#include <unordered_map>
#include <vector>
#include <string_view>
#include "gcool/LLVMIRGen/LLVMIRGen.h"
#include "gcool/AST/Expr.h"

using namespace gcool;

#define ASTCONTEXT TheSema->TheASTContext
#define SYMTBL TheSema->TheASTContext->Symtbl

ir::LLVMIRGen::LLVMIRGen(sema::Sema* sema)
    : Context()
    , Module("Main", Context)
    , IRBuilder(Context)
    , BuiltObjHold(llvm::IntegerType::getInt32PtrTy(Context))
    , BuiltIntTy(llvm::Type::getInt64Ty(Context))
    , BuiltFloatTy(llvm::Type::getDoubleTy(Context))
    , BuiltBoolTy(llvm::Type::getInt1Ty(Context))
    , ClassInfoTy(llvm::StructType::create(Context, "ClassInfo"))
    , ClassInfoSize(4) // N pointer
    , VMethodSlotTy(llvm::FunctionType::get(llvm::Type::getInt32Ty(Context), true)->getPointerTo())
    , VTableTy(llvm::StructType::create(
        Context,
        {ClassInfoTy, VMethodSlotTy},
        "VTable", true
        ))
    , VTableRefTy(VTableTy->getPointerTo())
    , TheSema(sema)
{
    ClassInfoTy->setBody({
        VTableRefTy,                     // SuperClass VTableRef
        llvm::Type::getInt64Ty(Context), // inheritDepth
        BuiltObjHold, BuiltObjHold},     // holder
        true);
}

ir::LLVMIRGen::~LLVMIRGen() = default;

bool ir::LLVMIRGen::emitLLVMIR() {
    if (TheSema->TheErrorList.size() != 0) {
        return false;
    }
    pass1();
    pass2();
    pass3();
    return true;
}

void ir::LLVMIRGen::pass1() {
    // FatPointer
    for(auto& c : ASTCONTEXT->Classes) {
        if (c.Annotation->TheClassKind == sema::ClassAnnotation::CK_Abstract) continue;
        if (c.Annotation->TheClassKind == sema::ClassAnnotation::CK_Primitive) {
            auto fp = addFatPointer(c.Name);
            fp->setBody({VTableRefTy, BuiltObjHold}, true);
        } else {
            auto fp = addFatPointer(c.Name);
            auto obj = addObjectStruct(c.Name);
            fp->setBody({VTableRefTy, obj}, true);
        }
    }
}

void ir::LLVMIRGen::pass2() {
    TypeList typeListBuf;
    ConstantList vmethodBuf;
    std::string funcNameBuf;
    for(auto& c : ASTCONTEXT->Annotation->InheritOrder) {
        auto selfFT = getFatPointer(c->Name);

        // ObjectStruct Defination, Primitive Class use special implement
        if (c->Annotation->TheClassKind != sema::ClassAnnotation::CK_Primitive) {
            typeListBuf.clear();
            typeListBuf.reserve(c->Attrs.size() + 1);
            auto superClass = c->Annotation->SuperClass;
            if (superClass != nullptr) 
                typeListBuf.push_back(getObjectStruct(c->Inheirt));
            for (auto& a : c->Attrs)
                typeListBuf.push_back(getFatPointer(a.Formal.Type));
            getObjectStruct(c->Name)->setBody(typeListBuf, true);
        }
    
        // MethodDecl
        // new method for operator new
        auto ft = llvm::FunctionType::get(selfFT, {}, false);
        llvm::Function::Create(
                ft, llvm::GlobalValue::LinkageTypes::ExternalLinkage,
                llvm::StringRef(c->Name.getName()) + "_" + SYMTBL.getNewMethod().getName(), 
                Module);
        for (auto& m : c->Methods) {
            if (m.Name == SYMTBL.getNewMethod()) continue;
            // param type
            typeListBuf.clear();
            typeListBuf.reserve(m.FormalParams.size() + 1);
            typeListBuf.push_back(selfFT);
            for(auto& p : m.FormalParams)
                typeListBuf.push_back(getFatPointer(p.Type));
            // return type
            auto retType = selfFT;
            if (m.RetType != SYMTBL.getSelfType())
                retType = getFatPointer(m.RetType);
            // function type
            auto ft = llvm::FunctionType::get(
                retType,
                typeListBuf,
                false
                );
            // funtion
            llvm::Function::Create(
                ft, llvm::GlobalValue::LinkageTypes::ExternalLinkage,
                llvm::StringRef(c->Name.getName()) + "_" + m.Name.getName(), 
                Module);
        }

        // VTable defination
        vmethodBuf.clear();
        vmethodBuf.resize(c->Annotation->MethodOffsetEnd, nullptr);
        auto curcp = c;
        do {
            for (auto& m : curcp->Methods) {
                if (vmethodBuf[m.Annotation->MethodOffset] == nullptr) {
                    funcNameBuf = curcp->Name.getName();
                    funcNameBuf.append("_").append(m.Name.getName());
                    auto f = Module.getFunction(funcNameBuf);
                    assert(f != nullptr && "getfunction befor decl");
                    vmethodBuf[m.Annotation->MethodOffset] = llvm::ConstantExpr::getBitCast(
                        f,
                        VMethodSlotTy
                    );
                }
            }
            curcp = curcp->Annotation->SuperClass;
        } while(curcp != nullptr);
        assert([&vmethodBuf](){
            for (auto& slot : vmethodBuf)
                if (slot == nullptr) return false;
            return true;
        }() && "vtable has empty slot");
        addVTable(c->Name, c, vmethodBuf);
    }
}

void ir::LLVMIRGen::pass3() {
    
}

std::string_view ir::LLVMIRGen::bufName(std::string_view lhs, std::string_view rhs) {
    auto concatName = new char[lhs.length() + rhs.length() + 1];
    auto p = concatName;
    for (char c : lhs) *p++ = c;
    for (char c : rhs) *p++ = c;
    *p = 0;
    NameBufList.push_back(concatName);
    return { concatName };
}

llvm::StructType* ir::LLVMIRGen::addFatPointer(ast::Symbol classNameS) {
    auto name = bufName(classNameS.getName(), "FP");
    auto fp = llvm::StructType::create(Context, name);
    FatPointerTyMap.insert({classNameS, fp});
    return fp;
}

llvm::StructType* ir::LLVMIRGen::getFatPointer(ast::Symbol classNameS) {
    auto p = FatPointerTyMap.find(classNameS);
    assert(p != FatPointerTyMap.end() && "getFatPointer before add");
    return p->second;
}

llvm::StructType* ir::LLVMIRGen::addObjectStruct(ast::Symbol classNameS) {
    auto name = bufName(classNameS.getName(), "Obj");
    auto obj = llvm::StructType::create(Context, name);
    ObejctTyMap.insert({classNameS, obj});
    return obj;
}

llvm::StructType* ir::LLVMIRGen::getObjectStruct(ast::Symbol classNameS) {
    auto p = ObejctTyMap.find(classNameS);
    assert(p != ObejctTyMap.end() && "getObjectStruct before add");
    return p->second;
}

// super class should already decl VTable
llvm::GlobalVariable* ir::LLVMIRGen::addVTable(ast::Symbol classNameS, 
    ast::Class* classInfo, llvm::ArrayRef<llvm::Constant*> methodInit) {
    auto vtArrayTy = llvm::ArrayType::get(VMethodSlotTy, methodInit.size());
    auto vtTy = llvm::StructType::get(Context, {ClassInfoTy, vtArrayTy}, true);
    llvm::Constant* superClassVTable;
    if (classInfo->Annotation->SuperClass == nullptr)
        superClassVTable = llvm::Constant::getNullValue(VTableRefTy);
    else
        superClassVTable = llvm::ConstantExpr::getBitCast(getVTable(classInfo->Inheirt), VTableRefTy);
    auto vtVal = llvm::ConstantStruct::get(
        vtTy,{
        llvm::ConstantStruct::get(
            ClassInfoTy, {
                superClassVTable,
                llvm::ConstantInt::get(llvm::Type::getInt64Ty(Context), llvm::APInt(64, classInfo->Annotation->InheritDepth)),
                llvm::Constant::getNullValue(BuiltObjHold),
                llvm::Constant::getNullValue(BuiltObjHold),
            }),
        llvm::ConstantArray::get(vtArrayTy, methodInit)
        });
    auto globalVt = new llvm::GlobalVariable(
        Module, vtTy, true, 
        llvm::GlobalValue::ExternalLinkage,
        vtVal,
        llvm::StringRef(classNameS.getName()) + "VT");
    VTableMap.insert({classNameS, globalVt});
    return globalVt;
}

llvm::GlobalVariable* ir::LLVMIRGen::getVTable(ast::Symbol classNameS) {
    auto p = VTableMap.find(classNameS);
    assert(p != VTableMap.end() && "getVTable before add");
    return p->second;
}



void ir::LLVMIRGen::print(llvm::raw_ostream& os) {
    Module.print(os, nullptr);
}

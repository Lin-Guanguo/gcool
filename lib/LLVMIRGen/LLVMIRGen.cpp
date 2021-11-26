#include <unordered_map>
#include <vector>
#include <string_view>
#include "gcool/LLVMIRGen/LLVMIRGen.h"
#include "gcool/AST/Expr.h"

using namespace gcool;

#define ASTCONTEXT TheSema->TheASTContext

ir::LLVMIRGen::LLVMIRGen(sema::Sema* sema)
    : Context()
    , Module("Main", Context)
    , IRBuilder(Context)
    , BuiltObjHold(llvm::IntegerType::getInt32PtrTy(Context))
    , BuiltIntTy(llvm::Type::getInt64Ty(Context))
    , BuiltFloatTy(llvm::Type::getDoubleTy(Context))
    , BuiltBoolTy(llvm::Type::getInt1Ty(Context))
    , VTableSlotTy(llvm::FunctionType::get(llvm::Type::getInt32Ty(Context), true)->getPointerTo())
    , VTableTy(VTableSlotTy->getPointerTo())
    , TheSema(sema)
{

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
    //this->emitRuntime(); // GCoolRuntimeIR.cpp
}

void ir::LLVMIRGen::pass2() {
    // FatPointer
    for(auto& c : ASTCONTEXT->Classes) {
        if (c.Annotation->TheClassKind == sema::ClassAnnotation::CK_Abstract) continue;
        auto className = c.Name.getName();
        if (c.Annotation->TheClassKind == sema::ClassAnnotation::CK_Builtin) {
            auto fp = addFatPointer(className);
            fp->setBody({VTableTy, BuiltObjHold}, true);
        } else {
            auto fp = addFatPointer(className);
            auto obj = addObjectStruct(className);
            fp->setBody({VTableTy, obj}, true);
        }
    }
    TypeList bufTypeList;
    for(auto& c : ASTCONTEXT->Classes) {
        if (c.Annotation->TheClassKind == sema::ClassAnnotation::CK_Abstract) continue;
        auto className = c.Name.getName();
        auto selfFT = getFatPointer(className);

        // ObjectStruct Defination
        if (c.Annotation->TheClassKind != sema::ClassAnnotation::CK_Builtin) {
            bufTypeList.clear();
            bufTypeList.reserve(c.Attrs.size());
            for (auto& a : c.Attrs)
                bufTypeList.push_back(getFatPointer(a.Formal.Type.getName()));
            getObjectStruct(className)->setBody(bufTypeList, true);
        }
    
        // MethodDecl
        // 0new method for operator new
        auto ft = llvm::FunctionType::get(selfFT, {}, false);
        llvm::Function::Create(
                ft, llvm::GlobalValue::LinkageTypes::ExternalLinkage,
                llvm::StringRef(className) + "_" + ASTCONTEXT->Symtbl.getNewMethod().getName(), 
                Module);
        for (auto& m : c.Methods) {
            if (m.Name == ASTCONTEXT->Symtbl.getNewMethod()) continue;
            // param type
            bufTypeList.clear();
            bufTypeList.reserve(m.FormalParams.size() + 1);
            bufTypeList.push_back(selfFT);
            for(auto& p : m.FormalParams)
                bufTypeList.push_back(getFatPointer(p.Type.getName()));
            // return type
            auto retType = selfFT;
            if (m.RetType != ASTCONTEXT->Symtbl.getSelfType())
                retType = getFatPointer(m.RetType.getName());
            // function type
            auto ft = llvm::FunctionType::get(
                retType,
                bufTypeList,
                false
                );
            // funtion
            llvm::Function::Create(
                ft, llvm::GlobalValue::LinkageTypes::ExternalLinkage,
                llvm::StringRef(className) + "_" + m.Name.getName(), 
                Module);
        }
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

llvm::StructType* ir::LLVMIRGen::addFatPointer(std::string_view className) {
    auto name = bufName(className, "FP");
    auto fp = llvm::StructType::create(Context, name);
    FatPointerTyMap.insert({className, fp});
    return fp;
}

llvm::StructType* ir::LLVMIRGen::getFatPointer(std::string_view className) {
    auto p = FatPointerTyMap.find(className);
    assert(p != FatPointerTyMap.end() && "getFatPointer before add");
    return p->second;
}

llvm::StructType* ir::LLVMIRGen::addObjectStruct(std::string_view className) {
    auto name = bufName(className, "Obj");
    auto obj = llvm::StructType::create(Context, name);
    ObejctTyMap.insert({className, obj});
    return obj;
}

llvm::StructType* ir::LLVMIRGen::getObjectStruct(std::string_view className) {
    auto p = ObejctTyMap.find(className);
    assert(p != ObejctTyMap.end() && "getObjectStruct before add");
    return p->second;
}

llvm::Constant* ir::LLVMIRGen::addVTable(std::string_view className, llvm::ArrayRef<llvm::Constant*> init) {
    auto vtArrayTy = llvm::ArrayType::get(VTableSlotTy, init.size());
    auto vt = llvm::ConstantExpr::getBitCast(
        new llvm::GlobalVariable(
            Module, vtArrayTy, true, 
            llvm::GlobalValue::ExternalLinkage,
            llvm::ConstantArray::get(vtArrayTy, init), 
            llvm::StringRef(className) + "VT"), 
        VTableTy);;
    VTableMap.insert({className, vt});
    return vt;
}

llvm::Constant* ir::LLVMIRGen::getVTable(std::string_view className) {
    auto p = VTableMap.find(className);
    assert(p != VTableMap.end() && "getVTable before add");
    return p->second;
}



void ir::LLVMIRGen::print(llvm::raw_ostream& os) {
    Module.print(os, nullptr);
}

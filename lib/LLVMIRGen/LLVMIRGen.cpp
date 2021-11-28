#include "gcool/LLVMIRGen/LLVMIRGen.h"

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
    , VMethodSlotTy(llvm::FunctionType::get(llvm::Type::getInt32Ty(Context), true)->getPointerTo())
    , VTableTy(llvm::StructType::create(
        Context,
        {ClassInfoTy, llvm::ArrayType::get(VMethodSlotTy, 0)},
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
    for(auto& c : ASTCONTEXT->Annotation->InheritOrder) {
        llvm::StructType* fp;
        switch(c->Annotation->TheClassKind) {
        case sema::ClassAnnotation::CK_Object:
            fp = addFatPointer(c->Name);
            ObjectRefTy = addObjectStruct(c->Name)->getPointerTo();
            break;
        case sema::ClassAnnotation::CK_Primitive:
            fp = addFatPointer(c->Name);
            break;
        case sema::ClassAnnotation::CK_Trivial:
            fp = addFatPointer(c->Name);
            addObjectStruct(c->Name);
            break;
        default:
            assert(0 && "nerver reach here");
        }
        fp->setBody({VTableRefTy, ObjectRefTy}, true);
    }
}

void ir::LLVMIRGen::pass2() {
    TypeList typeListBuf;
    ConstantList vmethodBuf;
    for(auto& c : ASTCONTEXT->Annotation->InheritOrder) {
        auto selfFP = getFatPointer(c->Name);

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
        auto newMethodft = llvm::FunctionType::get(selfFP, {}, false);
        auto newMethod = addMethod(newMethodft, c->Name, SYMTBL.getNewMethod());
        // initMethod
        if (c->Annotation->TheClassKind != sema::ClassAnnotation::CK_Primitive) {
            auto initMethodft = llvm::FunctionType::get(llvm::Type::getVoidTy(Context), {selfFP}, false);
            auto initMethod = addMethod(initMethodft, c->Name, SYMTBL.getInitMethod());
        }
        for (auto& m : c->Methods) {
            if (m.Name == SYMTBL.getNewMethod()) continue;
            // param type
            typeListBuf.clear();
            typeListBuf.reserve(m.FormalParams.size() + 1);
            typeListBuf.push_back(selfFP);
            for(auto& p : m.FormalParams)
                typeListBuf.push_back(getFatPointer(p.Type));
            // return type
            auto retType = selfFP;
            if (m.RetType != SYMTBL.getSelfType())
                retType = getFatPointer(m.RetType);
            // function type
            auto ft = llvm::FunctionType::get(retType, typeListBuf, false);
            // funtion
            addMethod(ft, c->Name, m.Name);
        }

        // VTable defination
        vmethodBuf.clear();
        vmethodBuf.resize(c->Annotation->MethodOffsetEnd, nullptr);
        auto curcp = c;
        do {
            for (auto& m : curcp->Methods) {
                if (vmethodBuf[m.Annotation->MethodOffset] == nullptr) {
                    auto f = getMethod(curcp->Name, m.Name);
                    vmethodBuf[m.Annotation->MethodOffset] = llvm::ConstantExpr::getBitCast(
                        f, VMethodSlotTy);
                }
            }
            curcp = curcp->Annotation->SuperClass;
        } while(curcp != nullptr);
        vmethodBuf[0] = llvm::ConstantExpr::getBitCast(newMethod, VMethodSlotTy);
        assert([&vmethodBuf](){
            for (auto& slot : vmethodBuf)
                if (slot == nullptr) return false;
            return true;
        }() && "vtable has empty slot");
        addVTable(c->Name, c, vmethodBuf);
    }
}

void ir::LLVMIRGen::pass3() {
    emitNative();
    for (auto* c : ASTCONTEXT->Annotation->InheritOrder) {
        if (c->Annotation->TheClassKind != sema::ClassAnnotation::CK_Trivial) continue;
        emitNewMethod(c);
        for (auto& m : c->Methods){
            //emitMethod(c, &m);
        }
    }
}

void ir::LLVMIRGen::emitNewMethod(ast::Class* c) {
    auto newMethod = getMethod(c->Name, SYMTBL.getNewMethod());
    auto BB = llvm::BasicBlock::Create(Context, "entry", newMethod);
    IRBuilder.SetInsertPoint(BB);
    auto heapObj = IRBuilder.CreateCall(
        getBuiltinFunction(BK_Malloc), 
        {llvm::ConstantInt::get(Context, llvm::APInt(64, 64 * 2 * c->Annotation->AttrOffsetEnd))},
        "heapObj");
    auto retval = IRBuilder.CreateInsertValue(
        llvm::UndefValue::get(getFatPointer(c->Name)), 
        getVTableConstant(c->Name), {0});
    retval = IRBuilder.CreateInsertValue(retval,
        IRBuilder.CreateBitCast(heapObj, ObjectRefTy), {1});
    IRBuilder.CreateCall(getMethod(c->Inheirt, SYMTBL.getInitMethod()), {retval});
    IRBuilder.CreateCall(getMethod(c->Name, SYMTBL.getInitMethod()), {retval});
    IRBuilder.CreateRet(retval);

    // Init Method
    auto initMethod = getMethod(c->Name, SYMTBL.getInitMethod());
    BB = llvm::BasicBlock::Create(Context, "entry", initMethod);
    IRBuilder.SetInsertPoint(BB);
    auto initFP = initMethod->arg_begin();
    auto initObjRef = IRBuilder.CreateExtractValue(initFP, {1});
    auto attrList = IRBuilder.CreateBitCast(initObjRef, 
        llvm::ArrayType::get(getFatPointer(SYMTBL.getObject()), 0)->getPointerTo());
    for (auto& a : c->Attrs) {
        if (a.Init.has_value()) {
            auto val = emitExpr(a.Init.value());
            auto fp = IRBuilder.CreateGEP(
                llvm::ArrayType::get(getFatPointer(SYMTBL.getObject()), 0),
                attrList, {
                    llvm::ConstantInt::get(Context, llvm::APInt(32, 0)),
                    llvm::ConstantInt::get(Context, llvm::APInt(32, a.Annotation->AttrOffset))
                });
            IRBuilder.CreateStore(val, fp);
        }
    }
    IRBuilder.CreateRet(nullptr);
}

void ir::LLVMIRGen::emitMethod(ast::Class* c, ast::MethodFeature* m) {
    auto methodFunc = getMethod(c->Name, m->Name);
    auto BB = llvm::BasicBlock::Create(Context, "entry", methodFunc);
    IRBuilder.SetInsertPoint(BB);
    auto val = emitExpr(m->Body);
    IRBuilder.CreateRet(val);
}

llvm::StructType* ir::LLVMIRGen::addFatPointer(ast::Symbol classNameS) {
    TempStringBuf = classNameS.getName();
    TempStringBuf.append("FP");
    auto fp = llvm::StructType::create(Context, TempStringBuf);
    FatPointerTyMap.insert({classNameS, fp});
    return fp;
}

llvm::StructType* ir::LLVMIRGen::getFatPointer(ast::Symbol classNameS) {
    // TODO: use better way to bit cast FatPointerStruct, 
    //       now all FatPointer use the same struct

    // auto p = FatPointerTyMap.find(classNameS);
    auto p = FatPointerTyMap.find(SYMTBL.getObject());
    assert(p != FatPointerTyMap.end() && "getFatPointer before add");
    return p->second;
}

llvm::StructType* ir::LLVMIRGen::addObjectStruct(ast::Symbol classNameS) {
    TempStringBuf = classNameS.getName();
    TempStringBuf.append("Obj");
    auto obj = llvm::StructType::create(Context, TempStringBuf);
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
        superClassVTable = getVTableConstant(classInfo->Inheirt);
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

llvm::Constant* ir::LLVMIRGen::getVTableConstant(ast::Symbol className) {
    return llvm::ConstantExpr::getBitCast(getVTable(className), VTableRefTy);
}

llvm::Function* ir::LLVMIRGen::addMethod(llvm::FunctionType* ft, ast::Symbol classNameS, ast::Symbol methodNameS) {
    auto f = llvm::Function::Create(
        ft, llvm::GlobalValue::LinkageTypes::ExternalLinkage,
        llvm::StringRef(classNameS.getName()) + "." + methodNameS.getName(), 
        Module);
    return f;
}

llvm::Function* ir::LLVMIRGen::getMethod(ast::Symbol classNameS, ast::Symbol methodNameS) {
    TempStringBuf = classNameS.getName();
    TempStringBuf.append(".").append(methodNameS.getName());
    auto f = Module.getFunction(TempStringBuf);
    assert(f && "get method for declare");
    return f;
}

llvm::Function* ir::LLVMIRGen::getBuiltinFunction(BuiltinFunctionKind Bk) {
    switch (Bk)
    {
    case BK_Malloc: return Module.getFunction("gcool_malloc"); break;
    default: assert(0 && "get Undecl Builtin Funtion");
    }   
}

void ir::LLVMIRGen::print(llvm::raw_ostream& os) {
    Module.print(os, nullptr);
}

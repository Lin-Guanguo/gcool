#include "gcool/LLVMIRGen/LLVMIRGen.h"

using namespace gcool;

#define ASTCONTEXT TheSema->TheASTContext
#define SYMTBL TheSema->TheASTContext->Symtbl

#define CONSTINT32(val) llvm::ConstantInt::get(Context, llvm::APInt(32, val))
#define CONSTINT64(val) llvm::ConstantInt::get(Context, llvm::APInt(64, val))

ir::LLVMIRGen::LLVMIRGen(sema::Sema* sema)
    : Context()
    , Module("Main", Context)
    , IRBuilder(Context)
    , Holder64bit(llvm::IntegerType::getInt32PtrTy(Context))
    , BuiltIntTy(llvm::Type::getInt64Ty(Context))
    , BuiltFloatTy(llvm::Type::getDoubleTy(Context))
    , BuiltBoolTy(llvm::Type::getInt1Ty(Context))
    , FatPointerTy(llvm::StructType::create(Context, "FatPointer"))
    // vtable
    , ClassInfoTy(llvm::StructType::create(Context, "ClassInfo"))
    , VMethodSlotTy(llvm::FunctionType::get(llvm::Type::getInt32Ty(Context), true)->getPointerTo())
    , VTableTy(llvm::StructType::create(
        Context,
        {ClassInfoTy, llvm::ArrayType::get(VMethodSlotTy, 0)},
        "VTable", true))
    , VTableRefTy(VTableTy->getPointerTo())
    // heapObj
    , HeapObjTy(llvm::ArrayType::get(FatPointerTy, 0))
    , HeapObjRefTy(HeapObjTy->getPointerTo())
    , TheSema(sema)
{
    FatPointerTy->setBody({
        VTableRefTy,
        HeapObjRefTy},
        true);
    ClassInfoTy->setBody({
        VTableRefTy,                     // SuperClass VTableRef
        llvm::Type::getInt64Ty(Context)}, // inheritDepth
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

}

void ir::LLVMIRGen::pass2() {
    TypeList typeListBuf;
    ConstantList vmethodBuf;
    for(auto& c : ASTCONTEXT->Annotation->InheritOrder) {
        // MethodDecl
        // new method for operator new
        auto newMethodft = llvm::FunctionType::get(FatPointerTy, {}, false);
        auto newMethod = addMethod(newMethodft, c->Name, SYMTBL.getNewMethod());
        // initMethod
        if (c->Annotation->TheClassKind != sema::ClassAnnotation::CK_Primitive) {
            auto initMethodft = llvm::FunctionType::get(llvm::Type::getVoidTy(Context), {FatPointerTy}, false);
            addMethod(initMethodft, c->Name, SYMTBL.getInitMethod());
        }
        for (auto& m : c->Methods) {
            if (m.Name == SYMTBL.getNewMethod()) continue;
            typeListBuf.resize(m.FormalParams.size() + 1, FatPointerTy);
            auto ft = llvm::FunctionType::get(FatPointerTy, typeListBuf, false);
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
        // add generate new
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
        for (auto& m : c->Methods) {
            emitMethod(c, &m);
        }
    }
    emitDeriver();
}

void ir::LLVMIRGen::emitNewMethod(ast::Class* c) {
    auto newMethod = getMethod(c->Name, SYMTBL.getNewMethod());
    auto BB = llvm::BasicBlock::Create(Context, "entry", newMethod);
    IRBuilder.SetInsertPoint(BB);
    auto heapObj = IRBuilder.CreateCall(
        getBuiltinFunction(BK_Malloc), 
        {CONSTINT64(8 * 2 * c->Annotation->AttrOffsetEnd)},
        "heapObj");
    auto retval = IRBuilder.CreateInsertValue(
        llvm::UndefValue::get(FatPointerTy), 
        getVTableConstant(c->Name), {0});
    retval = IRBuilder.CreateInsertValue(retval,
        IRBuilder.CreateBitCast(heapObj, HeapObjRefTy), {1});
    IRBuilder.CreateCall(getMethod(c->Name, SYMTBL.getInitMethod()), {retval});
    IRBuilder.CreateRet(retval);

    // Init Method
    auto initMethod = getMethod(c->Name, SYMTBL.getInitMethod());
    BB = llvm::BasicBlock::Create(Context, "entry", initMethod);
    IRBuilder.SetInsertPoint(BB);
    auto initFP = initMethod->arg_begin();
    IRBuilder.CreateCall(getMethod(c->Inheirt, SYMTBL.getInitMethod()), {initFP});
    auto initHeapObj = IRBuilder.CreateExtractValue(initFP, {1});
    llvm::AllocaInst* local = nullptr;
    if (c->Annotation->InitLocalVarN != 0)
        local = IRBuilder.CreateAlloca(FatPointerTy, CONSTINT32(c->Annotation->InitLocalVarN), "LocalVars");
    for (auto& a : c->Attrs) {
        if (a.Init.has_value()) {
            auto val = emitExpr(a.Init.value(), initFP, local);
            auto fp = IRBuilder.CreateGEP(
                HeapObjTy, initHeapObj, {
                    CONSTINT32(0), CONSTINT32(a.Annotation->AttrOffset)});
            IRBuilder.CreateStore(val, fp);
        }
    }
    IRBuilder.CreateRet(nullptr);
}

void ir::LLVMIRGen::emitMethod(ast::Class* c, ast::MethodFeature* m) {
    auto methodFunc = getMethod(c->Name, m->Name);
    auto BB = llvm::BasicBlock::Create(Context, "entry", methodFunc);
    IRBuilder.SetInsertPoint(BB);
    auto self = methodFunc->arg_begin();
    llvm::AllocaInst* local = nullptr;
    if (m->Annotation->BodyLocalVarN != 0)
        local = IRBuilder.CreateAlloca(FatPointerTy, CONSTINT32(m->Annotation->BodyLocalVarN), "LocalVars");
    int i = 0;
    for (auto arg = self + 1; arg != methodFunc->arg_end(); ++arg) {
        auto localvar = IRBuilder.CreateGEP(FatPointerTy, local, CONSTINT32(i), 
            m->FormalParams[i].Name.getName());
        IRBuilder.CreateStore(arg, localvar);
        ++i;
    }
    auto val = emitExpr(m->Body, self, local);
    IRBuilder.CreateRet(val);
}

void ir::LLVMIRGen::emitDeriver() {
    auto mainFt = llvm::FunctionType::get(  // i32 @main(i32 %argc, i8** %argv)
        llvm::IntegerType::getInt32Ty(Context), {
            llvm::IntegerType::getInt32Ty(Context),
            llvm::IntegerType::getInt8PtrTy(Context)->getPointerTo()
        }, false);
    auto mainFunc = llvm::Function::Create(mainFt, 
        llvm::GlobalValue::LinkageTypes::ExternalLinkage, "main", Module);
    auto BB = llvm::BasicBlock::Create(Context, "entry", mainFunc);
    IRBuilder.SetInsertPoint(BB);
    auto newMain = getMethod(SYMTBL.getMainClass(), SYMTBL.getNewMethod());
    auto objFP = IRBuilder.CreateCall(newMain, {});
    auto mainMethod = getMethod(SYMTBL.getMainClass(), SYMTBL.getMainMethod());
    auto mainRet = IRBuilder.CreateCall(mainMethod, {objFP});
    auto retVal = IRBuilder.CreateExtractValue(mainRet, {1});
    retVal = IRBuilder.CreateTrunc(
        IRBuilder.CreatePtrToInt(retVal, BuiltIntTy), 
        llvm::IntegerType::getInt32Ty(Context));
    IRBuilder.CreateRet(retVal);
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
                CONSTINT64(classInfo->Annotation->InheritDepth)
            }),
        llvm::ConstantArray::get(vtArrayTy, methodInit)});
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

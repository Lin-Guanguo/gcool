#include "gcool/LLVMIRGen/LLVMIRGen.h"

using namespace gcool;

#define ASTCONTEXT TheSema->TheASTContext
#define SYMTBL TheSema->TheASTContext->Symtbl

void ir::LLVMIRGen::emitNative() {
    auto ObjectS = SYMTBL.getObject();
    ast::Symbol BoolS = SYMTBL.getBool();

    // builtinFunction
    auto mallocft = llvm::FunctionType::get(
        llvm::IntegerType::getInt8PtrTy(Context), 
        {llvm::IntegerType::getInt64Ty(Context)}, false);
    auto mallocFunc = llvm::Function::Create(mallocft, 
        llvm::GlobalValue::LinkageTypes::ExternalLinkage, "gcool_malloc", Module);    

    // Obejct
    { // Object.0new
        auto func = getMethod(ObjectS, SYMTBL.getNewMethod());
        auto BB = llvm::BasicBlock::Create(Context, "entry", func);
        IRBuilder.SetInsertPoint(BB);
        auto obj = IRBuilder.CreateCall(mallocFunc, 
            {llvm::ConstantInt::get(Context, llvm::APInt(64, 0))},
            "obj");
        auto retval = IRBuilder.CreateInsertValue(
            llvm::ConstantStruct::get(FatPointerTy, {getVTableConstant(ObjectS), llvm::UndefValue::get(HeapObjRefTy)}), 
            IRBuilder.CreateBitCast(obj, HeapObjRefTy), {1});
        IRBuilder.CreateRet(retval);
    } { // Object.0init
        auto func = getMethod(ObjectS, SYMTBL.getInitMethod());
        auto BB = llvm::BasicBlock::Create(Context, "entry", func);
        IRBuilder.SetInsertPoint(BB);
        IRBuilder.CreateRet(nullptr);
    } { // Object.opisvoid
        auto func = getMethod(ObjectS, SYMTBL.get("opisvoid"));
        auto BB = llvm::BasicBlock::Create(Context, "entry", func);
        IRBuilder.SetInsertPoint(BB);
        auto retval = llvm::ConstantStruct::get(FatPointerTy, {
            getVTableConstant(BoolS), 
            llvm::ConstantExpr::getIntToPtr(llvm::ConstantInt::get(Context, llvm::APInt(64, 1)), HeapObjRefTy)});
        IRBuilder.CreateRet(retval);
    }

    // Int Float Bool new method
    ast::Symbol className[] =
        {SYMTBL.getInt(), SYMTBL.getFloat(), SYMTBL.getBool()};
    for (int i = 0; i < 3; ++i) { // Int_0new
        auto func = getMethod(className[i], SYMTBL.getNewMethod());
        auto BB = llvm::BasicBlock::Create(Context, "entry", func);
        IRBuilder.SetInsertPoint(BB);
        auto retval = llvm::ConstantStruct::get(FatPointerTy, 
            {getVTableConstant(className[i]), llvm::UndefValue::get(HeapObjRefTy)});
        IRBuilder.CreateRet(retval);
    }
    // Int Float arith
    ast::Symbol methods[] = {
        SYMTBL.get("opadd"), SYMTBL.get("opsub"), SYMTBL.get("opmul"), SYMTBL.get("opdiv"),
        SYMTBL.get("opeq"), SYMTBL.get("opge"), SYMTBL.get("opgt"), SYMTBL.get("ople"),  SYMTBL.get("oplt")
    };
    for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 9; ++j) {
        auto func = getMethod(className[i], methods[j]);
        auto BB = llvm::BasicBlock::Create(Context, "entry", func);
        IRBuilder.SetInsertPoint(BB);
        auto arg = func->arg_begin();
        auto v1 = IRBuilder.CreateExtractValue(arg, {1});
        auto v2 = IRBuilder.CreateExtractValue(++arg, {1});
        llvm::Value* arithRes;
        if (i == 0) {
            v1 = IRBuilder.CreatePtrToInt(v1, BuiltIntTy);
            v2 = IRBuilder.CreatePtrToInt(v2, BuiltIntTy);
            switch (j) {
            case 0: arithRes = IRBuilder.CreateAdd(v1, v2); break;
            case 1: arithRes = IRBuilder.CreateSub(v1, v2); break;
            case 2: arithRes = IRBuilder.CreateMul(v1, v2); break;
            case 3: arithRes = IRBuilder.CreateSDiv(v1, v2); break;
            case 4: arithRes = IRBuilder.CreateCmp(llvm::CmpInst::Predicate::ICMP_EQ, v1, v2); break;
            case 5: arithRes = IRBuilder.CreateCmp(llvm::CmpInst::Predicate::ICMP_SGE, v1, v2); break;
            case 6: arithRes = IRBuilder.CreateCmp(llvm::CmpInst::Predicate::ICMP_SGT, v1, v2); break;
            case 7: arithRes = IRBuilder.CreateCmp(llvm::CmpInst::Predicate::ICMP_SLE, v1, v2); break;
            case 8: arithRes = IRBuilder.CreateCmp(llvm::CmpInst::Predicate::ICMP_SLT, v1, v2); break;
            default: assert(0 && "never reach");
            }
        } else if (i == 1) {
            v1 = IRBuilder.CreateBitCast(
                IRBuilder.CreatePtrToInt(v1, BuiltIntTy), BuiltFloatTy);
            v2 = IRBuilder.CreateBitCast(
                IRBuilder.CreatePtrToInt(v2, BuiltIntTy), BuiltFloatTy);
            switch (j) {
            case 0: arithRes = IRBuilder.CreateFAdd(v1, v2); break;
            case 1: arithRes = IRBuilder.CreateFSub(v1, v2); break;
            case 2: arithRes = IRBuilder.CreateFMul(v1, v2); break;
            case 3: arithRes = IRBuilder.CreateFDiv(v1, v2); break;
            case 4: arithRes = IRBuilder.CreateCmp(llvm::CmpInst::Predicate::FCMP_OEQ, v1, v2); break;
            case 5: arithRes = IRBuilder.CreateCmp(llvm::CmpInst::Predicate::FCMP_OGE, v1, v2); break;
            case 6: arithRes = IRBuilder.CreateCmp(llvm::CmpInst::Predicate::FCMP_OGT, v1, v2); break;
            case 7: arithRes = IRBuilder.CreateCmp(llvm::CmpInst::Predicate::FCMP_OLE, v1, v2); break;
            case 8: arithRes = IRBuilder.CreateCmp(llvm::CmpInst::Predicate::FCMP_OLT, v1, v2); break;
            default: assert(0 && "never reach");
            }
        } else
            assert(0 && "never reach");

        llvm::Value* retval;
        if (j < 4) {
            if (i == 0)
                arithRes = IRBuilder.CreateIntToPtr(arithRes, HeapObjRefTy);
            else
                arithRes = IRBuilder.CreateIntToPtr(
                    IRBuilder.CreateBitCast(arithRes, BuiltIntTy), HeapObjRefTy);
            retval = IRBuilder.CreateInsertValue(
                llvm::UndefValue::get(FatPointerTy), 
                getVTableConstant(className[i]), {0});
        }
        else {
            arithRes = IRBuilder.CreateIntToPtr(
                IRBuilder.CreateZExt(arithRes, BuiltIntTy), HeapObjRefTy);
            retval = IRBuilder.CreateInsertValue(
                llvm::UndefValue::get(FatPointerTy), 
                getVTableConstant(BoolS), {0});

        }
        retval = IRBuilder.CreateInsertValue(retval, arithRes, {1});
        IRBuilder.CreateRet(retval);
    }
    }
    // Bool arith
    ast::Symbol boolMethod[] = {
        SYMTBL.get("opadd"), SYMTBL.get("opmul"), SYMTBL.get("opeq")
    };
    for (int i = 0; i < 3; ++i) {
        auto func = getMethod(BoolS, boolMethod[i]);
        auto BB = llvm::BasicBlock::Create(Context, "entry", func);
        IRBuilder.SetInsertPoint(BB);
        auto arg = func->arg_begin();
        auto v1 = IRBuilder.CreateExtractValue(arg, {1});
        auto v2 = IRBuilder.CreateExtractValue(++arg, {1});
        v1 = IRBuilder.CreatePtrToInt(v1, BuiltIntTy);
        v2 = IRBuilder.CreatePtrToInt(v2, BuiltIntTy);
        llvm::Value* arithRes;
        switch (i) {
        case 0: arithRes = IRBuilder.CreateOr(v1, v2); break;
        case 1: arithRes = IRBuilder.CreateAnd(v1, v2); break;
        case 2: 
            v1 = IRBuilder.CreateTrunc(v1, BuiltBoolTy);
            v2 = IRBuilder.CreateTrunc(v2, BuiltBoolTy);
            arithRes = IRBuilder.CreateICmpEQ(v1, v2); break;
        default: assert(0 && "never reach");
        }
        arithRes = IRBuilder.CreateIntToPtr(arithRes, HeapObjRefTy);
        auto retval = IRBuilder.CreateInsertValue(
            llvm::ConstantStruct::get(FatPointerTy, {getVTableConstant(BoolS), llvm::UndefValue::get(HeapObjRefTy)}), 
            arithRes, {1});
        IRBuilder.CreateRet(retval);
    } {
        auto func = getMethod(BoolS, SYMTBL.get("opnot"));
        auto BB = llvm::BasicBlock::Create(Context, "entry", func);
        IRBuilder.SetInsertPoint(BB);
        auto arg = func->arg_begin();
        auto v1 = IRBuilder.CreateExtractValue(arg, {1});
        v1 = IRBuilder.CreatePtrToInt(v1, BuiltIntTy);
        auto arithRes = IRBuilder.CreateXor(v1, llvm::ConstantInt::get(Context, llvm::APInt(64, 1)));
        arithRes = IRBuilder.CreateIntToPtr(arithRes, HeapObjRefTy);
        auto retval = IRBuilder.CreateInsertValue(
            llvm::ConstantStruct::get(FatPointerTy, {getVTableConstant(BoolS), llvm::UndefValue::get(HeapObjRefTy)}), 
            arithRes, {1});
        IRBuilder.CreateRet(retval);
    }

    // String Method
    ast::Symbol stringMethod[] = {
        SYMTBL.getNewMethod(), SYMTBL.get("opadd"),
        SYMTBL.get("opeq"), SYMTBL.get("opge"), SYMTBL.get("opgt"), SYMTBL.get("ople"),  SYMTBL.get("oplt")
    };
    for (int i = 0; i < 7; ++i) {
        auto func = getMethod(SYMTBL.getString(), stringMethod[i]);
        auto BB = llvm::BasicBlock::Create(Context, "entry", func);
        IRBuilder.SetInsertPoint(BB);
        IRBuilder.CreateRet(llvm::UndefValue::get(FatPointerTy));
    }

    // NullType
    auto NullTypeS = SYMTBL.getNullType();
    {
        auto func = getMethod(NullTypeS, SYMTBL.getNewMethod());
        auto BB = llvm::BasicBlock::Create(Context, "entry", func);
        IRBuilder.SetInsertPoint(BB);
        auto retval = llvm::ConstantStruct::get(FatPointerTy, 
            {getVTableConstant(NullTypeS), llvm::UndefValue::get(HeapObjRefTy)});
        IRBuilder.CreateRet(retval);
    } {
        auto func = getMethod(NullTypeS, SYMTBL.get("opisvoid"));
        auto BB = llvm::BasicBlock::Create(Context, "entry", func);
        IRBuilder.SetInsertPoint(BB);
        auto retval = llvm::ConstantStruct::get(FatPointerTy, {
            getVTableConstant(BoolS), 
            llvm::ConstantExpr::getIntToPtr(llvm::ConstantInt::get(Context, llvm::APInt(64, 0)), HeapObjRefTy)});
        IRBuilder.CreateRet(retval);
    }

}
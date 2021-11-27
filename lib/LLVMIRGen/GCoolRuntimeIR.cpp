#include "gcool/LLVMIRGen/LLVMIRGen.h"

using namespace gcool;

#define ASTCONTEXT TheSema->TheASTContext
#define SYMTBL TheSema->TheASTContext->Symtbl

void ir::LLVMIRGen::emitNative() {
    ast::Symbol className[] =
        {SYMTBL.getInt(), SYMTBL.getFloat(), SYMTBL.getBool()};
    for (int i = 0; i < 3; ++i) { // Int_0new
        auto func = getMethod(className[i], SYMTBL.getNewMethod());
        auto BB = llvm::BasicBlock::Create(Context, "entry", func);
        IRBuilder.SetInsertPoint(BB);
        auto retval = IRBuilder.CreateInsertValue(
            llvm::UndefValue::get(
                getFatPointer(className[i])), 
            getVTableConstant(className[i]), {0});
        IRBuilder.CreateRet(retval);
    }
    ast::Symbol methods[] = {
        SYMTBL.get("opadd"), SYMTBL.get("opsub"), SYMTBL.get("opmul"), SYMTBL.get("opdiv"),
        SYMTBL.get("opeq"), SYMTBL.get("opge"), SYMTBL.get("opgt"), SYMTBL.get("ople"),  SYMTBL.get("oplt")
    };
    ast::Symbol BoolS = SYMTBL.getBool();
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
                arithRes = IRBuilder.CreateIntToPtr(arithRes, ObjectRefTy);
            else
                arithRes = IRBuilder.CreateIntToPtr(
                    IRBuilder.CreateBitCast(arithRes, BuiltIntTy), ObjectRefTy);
            retval = IRBuilder.CreateInsertValue(
                llvm::UndefValue::get(getFatPointer(className[i])), 
                getVTableConstant(className[i]), {0});
        }
        else {
            arithRes = IRBuilder.CreateIntToPtr(
                IRBuilder.CreateZExt(arithRes, BuiltIntTy), ObjectRefTy);
            retval = IRBuilder.CreateInsertValue(
                llvm::UndefValue::get(getFatPointer(BoolS)), 
                getVTableConstant(BoolS), {0});

        }
        retval = IRBuilder.CreateInsertValue(retval, arithRes, {1});
        IRBuilder.CreateRet(retval);
    }
    }
    ast::Symbol boolMethod[] = {
        SYMTBL.get("opadd"), SYMTBL.get("opmul")
    };
    for (int i = 0; i < 2; ++i) {
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
        default: assert(0 && "never reach");
        }
        arithRes = IRBuilder.CreateIntToPtr(arithRes, ObjectRefTy);
        auto retval = IRBuilder.CreateInsertValue(
            llvm::UndefValue::get(getFatPointer(BoolS)), 
            getVTableConstant(BoolS), {0});
        retval = IRBuilder.CreateInsertValue(retval, arithRes, {1});
        IRBuilder.CreateRet(retval);
    }
    { // bool opnot
        auto func = getMethod(BoolS, SYMTBL.get("opnot"));
        auto BB = llvm::BasicBlock::Create(Context, "entry", func);
        IRBuilder.SetInsertPoint(BB);
        auto arg = func->arg_begin();
        auto v1 = IRBuilder.CreateExtractValue(arg, {1});
        v1 = IRBuilder.CreatePtrToInt(v1, BuiltIntTy);
        llvm::Value* arithRes = IRBuilder.CreateNot(v1);
        arithRes = IRBuilder.CreateIntToPtr(arithRes, ObjectRefTy);
        auto retval = IRBuilder.CreateInsertValue(
            llvm::UndefValue::get(getFatPointer(BoolS)), 
            getVTableConstant(BoolS), {0});
        retval = IRBuilder.CreateInsertValue(retval, arithRes, {1});
        IRBuilder.CreateRet(retval);
    }

}


// void ir::LLVMIRGen::emitRuntime() {
//     // // Fat Pointer type dec
//     // auto IntP = llvm::StructType::create(Context, {VTableTy, BuiltIntTy}, "IntP");
//     // auto FloatP = llvm::StructType::create(Context, {VTableTy, BuiltFloatTy}, "FloatP");
//     // auto BoolP = llvm::StructType::create(Context, {VTableTy, BuiltBoolTy}, "BoolP");

//     // // ========================== Declaration ==========================

//     // llvm::Function* IntFunc[11];
//     // llvm::Constant* IntVT;
//     // {
//     //     constexpr int FuncN = 11;
//     //     auto IntFT0 = llvm::FunctionType::get(IntP, {}, false);
//     //     auto IntFT1 = llvm::FunctionType::get(BoolP, {IntP}, false);
//     //     auto IntFT2 = llvm::FunctionType::get(IntP, {IntP, IntP}, false);
//     //     auto IntFT3 = llvm::FunctionType::get(BoolP, {IntP, IntP}, false);
//     //     llvm::FunctionType* FuncTy[FuncN] = 
//     //         {IntFT0, IntFT1, IntFT2, IntFT2, IntFT2, IntFT2, IntFT3, IntFT3, IntFT3, IntFT3, IntFT3};
//     //     constexpr const char* FuncName[FuncN] =
//     //         { "Int_0new", "Int_opisvoid", "Int_opadd", "Int_opsub", "Int_opmul", "Int_opdiv", 
//     //           "Int_opeq", "Int_opge", "Int_opgt", "Int_ople", "Int_oplt" };
//     //     for (int i = 0; i < FuncN; ++i) 
//     //         IntFunc[i] = llvm::Function::Create(FuncTy[i], 
//     //             llvm::GlobalValue::ExternalLinkage,
//     //             FuncName[i], Module);
//     //     // vtable
//     //     llvm::Constant* vtableInit[FuncN];
//     //     for (int i = 0; i < FuncN; ++i)
//     //         vtableInit[i] = llvm::ConstantExpr::getBitCast(IntFunc[i], VTableSlotTy);
//     //     auto vtableTy = llvm::ArrayType::get(VTableSlotTy, FuncN);
//     //     IntVT = llvm::ConstantExpr::getBitCast(
//     //             new llvm::GlobalVariable(
//     //             Module, vtableTy, true, 
//     //             llvm::GlobalValue::ExternalLinkage,
//     //             llvm::ConstantArray::get(vtableTy, vtableInit), 
//     //             "IntVT"), 
//     //         VTableTy);
//     // }

//     // llvm::Function* FloatFunc[11];
//     // llvm::Constant* FloatVT;
//     // {
//     //     constexpr int FuncN = 11;
//     //     auto FT0 = llvm::FunctionType::get(FloatP, {}, false);
//     //     auto FT1 = llvm::FunctionType::get(BoolP, FloatP, false);
//     //     auto FT2 = llvm::FunctionType::get(FloatP, {FloatP, FloatP}, false);
//     //     auto FT3 = llvm::FunctionType::get(BoolP, {FloatP, FloatP}, false);
//     //     llvm::FunctionType* FuncTy[FuncN] = 
//     //         {FT0, FT1, FT2, FT2, FT2, FT2, FT3, FT3, FT3, FT3, FT3};
//     //     constexpr const char* FuncName[FuncN] =
//     //         { "Float_0new", "Float_opisvoid", "Float_opadd", "Float_opsub", "Float_opmul", "Float_opdiv", 
//     //           "Float_opeq", "Float_opge", "Float_opgt", "Float_ople", "Float_oplt" };
//     //     for (int i = 0; i < FuncN; ++i) 
//     //         FloatFunc[i] = llvm::Function::Create(FuncTy[i], 
//     //             llvm::GlobalValue::ExternalLinkage,
//     //             FuncName[i], Module);
//     //     // vtable
//     //     llvm::Constant* vtableInit[FuncN];
//     //     for (int i = 0; i < FuncN; ++i)
//     //         vtableInit[i] = llvm::ConstantExpr::getBitCast(FloatFunc[i], VTableSlotTy);
//     //     auto vtableTy = llvm::ArrayType::get(VTableSlotTy, FuncN);
//     //     FloatVT = llvm::ConstantExpr::getBitCast(
//     //             new llvm::GlobalVariable(
//     //             Module, vtableTy, true, 
//     //             llvm::GlobalValue::ExternalLinkage,
//     //             llvm::ConstantArray::get(vtableTy, vtableInit), 
//     //             "FloatVT"), 
//     //         VTableTy);;
//     // }

//     // llvm::Function* BoolFunc[6];
//     // llvm::Constant* BoolVT;
//     // {
//     //     constexpr int FuncN = 6;
//     //     auto FT1 = llvm::FunctionType::get(BoolP, {}, false);
//     //     auto FT2 = llvm::FunctionType::get(BoolP, {BoolP}, false);
//     //     auto FT3 = llvm::FunctionType::get(BoolP, {BoolP, BoolP}, false);
//     //     auto FT4 = llvm::FunctionType::get(BoolP, {BoolP}, false);
//     //     llvm::FunctionType* FuncTy[FuncN] = 
//     //         {FT1, FT2, FT3, FT3, FT3, FT4};
//     //     constexpr const char* FuncName[FuncN] =
//     //         { "Bool_0new", "Bool_opisvoid", "Bool_opadd", "Bool_opmul", "Bool_opeq", "Boop_opnot" };
//     //     for (int i = 0; i < FuncN; ++i) 
//     //         BoolFunc[i] = llvm::Function::Create(FuncTy[i], 
//     //             llvm::GlobalValue::ExternalLinkage,
//     //             FuncName[i], Module);
//     //     llvm::Constant* vtableInit[FuncN];
//     //     for (int i = 0; i < FuncN; ++i)
//     //         vtableInit[i] = llvm::ConstantExpr::getBitCast(BoolFunc[i], VTableSlotTy);
//     //     auto vtableTy = llvm::ArrayType::get(VTableSlotTy, FuncN);
//     //     BoolVT = llvm::ConstantExpr::getBitCast(
//     //             new llvm::GlobalVariable(
//     //             Module, vtableTy, true, 
//     //             llvm::GlobalValue::ExternalLinkage,
//     //             llvm::ConstantArray::get(vtableTy, vtableInit), 
//     //             "BoolVT"), 
//     //         VTableTy);;
//     // }

//     // // ========================== Defination ==========================
    
//     // // Int_opisvoid, Float_opisvoid, Bool_opisvoid
//     // for (auto func : {IntFunc[1], FloatFunc[1], BoolFunc[1]}) { 
//     //     auto BB = llvm::BasicBlock::Create(Context, "entry", func);
//     //     IRBuilder.SetInsertPoint(BB);
//     //     auto retval = IRBuilder.CreateInsertValue(llvm::UndefValue::get(BoolP), BoolVT, {0});
//     //     retval = IRBuilder.CreateInsertValue(retval,
//     //         llvm::ConstantInt::get(Context, llvm::APInt(1, 0)), {1});
//     //     IRBuilder.CreateRet(retval);
//     // }
//     // { // Int_0new
//     //     auto func = IntFunc[0];
//     //     auto BB = llvm::BasicBlock::Create(Context, "entry", func);
//     //     IRBuilder.SetInsertPoint(BB);
//     //     auto retval = IRBuilder.CreateInsertValue(llvm::UndefValue::get(IntP), IntVT, {0});
//     //     IRBuilder.CreateRet(retval);
//     // }
//     // // Int_opadd, Int_opsub, Int_opmul, Int_opdiv, Int_opeq, Int_opge, Int_opgt, Int_ople, Int_oplt
//     // for (int i = 2; i < 11; ++i) { 
//     //     auto func = IntFunc[i];
//     //     auto BB = llvm::BasicBlock::Create(Context, "entry", func);
//     //     IRBuilder.SetInsertPoint(BB);
//     //     auto arg = func->arg_begin();
//     //     auto v1 = IRBuilder.CreateExtractValue(arg, {1});
//     //     auto v2 = IRBuilder.CreateExtractValue(++arg, {1});
//     //     llvm::Value* arithRes;
//     //     switch (i) {
//     //     case 2: arithRes = IRBuilder.CreateAdd(v1, v2); break;
//     //     case 3: arithRes = IRBuilder.CreateSub(v1, v2); break;
//     //     case 4: arithRes = IRBuilder.CreateMul(v1, v2); break;
//     //     case 5: arithRes = IRBuilder.CreateSDiv(v1, v2); break;
//     //     case 6: arithRes = IRBuilder.CreateCmp(llvm::CmpInst::Predicate::ICMP_EQ, v1, v2); break;
//     //     case 7: arithRes = IRBuilder.CreateCmp(llvm::CmpInst::Predicate::ICMP_SGE, v1, v2); break;
//     //     case 8: arithRes = IRBuilder.CreateCmp(llvm::CmpInst::Predicate::ICMP_SGT, v1, v2); break;
//     //     case 9: arithRes = IRBuilder.CreateCmp(llvm::CmpInst::Predicate::ICMP_SLE, v1, v2); break;
//     //     case 10: arithRes = IRBuilder.CreateCmp(llvm::CmpInst::Predicate::ICMP_SLT, v1, v2); break;
//     //     default: assert(0 && "never reach");
//     //     }
//     //     llvm::Value* retval;
//     //     if (i < 6)
//     //         retval = IRBuilder.CreateInsertValue(llvm::UndefValue::get(IntP), IntVT, {0});
//     //     else
//     //         retval = IRBuilder.CreateInsertValue(llvm::UndefValue::get(BoolP), BoolVT, {0});
//     //     retval = IRBuilder.CreateInsertValue(retval, arithRes, {1});
//     //     IRBuilder.CreateRet(retval);
//     // }
//     // { // Float_0new
//     //     auto func = FloatFunc[0];
//     //     auto BB = llvm::BasicBlock::Create(Context, "entry", func);
//     //     IRBuilder.SetInsertPoint(BB);
//     //     auto retval = IRBuilder.CreateInsertValue(llvm::UndefValue::get(FloatP), FloatVT, {0});
//     //     IRBuilder.CreateRet(retval);
//     // }
//     // // Float_opadd, Float_opsub, Float_opmul, Float_opdiv, Float_opeq, Float_opge, Float_opgt, Float_ople, Float_oplt
//     // for (int i = 2; i < 11; ++i) { 
//     //     auto func = FloatFunc[i];
//     //     auto BB = llvm::BasicBlock::Create(Context, "entry", func);
//     //     IRBuilder.SetInsertPoint(BB);
//     //     auto arg = func->arg_begin();
//     //     auto v1 = IRBuilder.CreateExtractValue(arg, {1});
//     //     auto v2 = IRBuilder.CreateExtractValue(++arg, {1});
//     //     llvm::Value* arithRes;
//     //     switch (i) {
//     //     case 2: arithRes = IRBuilder.CreateFAdd(v1, v2); break;
//     //     case 3: arithRes = IRBuilder.CreateFSub(v1, v2); break;
//     //     case 4: arithRes = IRBuilder.CreateFMul(v1, v2); break;
//     //     case 5: arithRes = IRBuilder.CreateFDiv(v1, v2); break;
//     //     case 6: arithRes = IRBuilder.CreateCmp(llvm::CmpInst::Predicate::FCMP_OEQ, v1, v2); break;
//     //     case 7: arithRes = IRBuilder.CreateCmp(llvm::CmpInst::Predicate::FCMP_OGE, v1, v2); break;
//     //     case 8: arithRes = IRBuilder.CreateCmp(llvm::CmpInst::Predicate::FCMP_OGT, v1, v2); break;
//     //     case 9: arithRes = IRBuilder.CreateCmp(llvm::CmpInst::Predicate::FCMP_OLE, v1, v2); break;
//     //     case 10: arithRes = IRBuilder.CreateCmp(llvm::CmpInst::Predicate::FCMP_OLT, v1, v2); break;
//     //     default: assert(0 && "never reach");
//     //     }
//     //     llvm::Value* retval;
//     //     if (i < 6)
//     //         retval = IRBuilder.CreateInsertValue(llvm::UndefValue::get(FloatP), FloatVT, {0});
//     //     else
//     //         retval = IRBuilder.CreateInsertValue(llvm::UndefValue::get(BoolP), BoolVT, {0});
//     //     retval = IRBuilder.CreateInsertValue(retval, arithRes, {1});
//     //     IRBuilder.CreateRet(retval);
//     // }
//     // { // Bool_0new
//     //     auto func = BoolFunc[0];
//     //     auto BB = llvm::BasicBlock::Create(Context, "entry", func);
//     //     IRBuilder.SetInsertPoint(BB);
//     //     auto retval = IRBuilder.CreateInsertValue(llvm::UndefValue::get(BoolP), BoolVT, {0});
//     //     IRBuilder.CreateRet(retval);
//     // }
//     // { // Bool_opnot
//     //     auto func = BoolFunc[5];
//     //     auto BB = llvm::BasicBlock::Create(Context, "entry", func);
//     //     IRBuilder.SetInsertPoint(BB);
//     //     auto arg = func->arg_begin();
//     //     auto v1 = IRBuilder.CreateExtractValue(arg, {1});
//     //     auto arithRes = IRBuilder.CreateNot(v1);
//     //     auto retval = IRBuilder.CreateInsertValue(llvm::UndefValue::get(BoolP), BoolVT, {0});
//     //     retval = IRBuilder.CreateInsertValue(retval, arithRes, {1});
//     //     IRBuilder.CreateRet(retval);
//     // }
//     // // Float_opadd, Float_opmul, Float_opeq
//     // for (int i = 2; i < 5; ++i) { 
//     //     auto func = BoolFunc[i];
//     //     auto BB = llvm::BasicBlock::Create(Context, "entry", func);
//     //     IRBuilder.SetInsertPoint(BB);
//     //     auto arg = func->arg_begin();
//     //     auto v1 = IRBuilder.CreateExtractValue(arg, {1});
//     //     auto v2 = IRBuilder.CreateExtractValue(++arg, {1});
//     //     llvm::Value* arithRes;
//     //     switch (i) {
//     //     case 2: arithRes = IRBuilder.CreateOr(v1, v2); break;
//     //     case 3: arithRes = IRBuilder.CreateAnd(v1, v2); break;
//     //     case 4: arithRes = IRBuilder.CreateCmp(llvm::CmpInst::Predicate::ICMP_EQ, v1, v2); break;
//     //     default: assert(0 && "never reach");
//     //     }
//     //     llvm::Value* retval = IRBuilder.CreateInsertValue(llvm::UndefValue::get(BoolP), BoolVT, {0});
//     //     retval = IRBuilder.CreateInsertValue(retval, arithRes, {1});
//     //     IRBuilder.CreateRet(retval);
//     // }

// }

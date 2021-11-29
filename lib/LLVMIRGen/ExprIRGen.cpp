#include "gcool/LLVMIRGen/LLVMIRGen.h"
#include "gcool/AST/Expr.h"

using namespace gcool;

#define CONSTINT32(val) llvm::ConstantInt::get(Context, llvm::APInt(32, val))
#define CONSTINT64(val) llvm::ConstantInt::get(Context, llvm::APInt(64, val))

#define SYMCONCAT(sym, str) sym.getName() + llvm::StringRef(str)
#define CREATEBB(str) llvm::BasicBlock::Create(Context, str, IRBuilder.GetInsertBlock()->getParent())

namespace gcool {
namespace ir {

#define ASTCONTEXT IRGen.TheSema->TheASTContext
#define SYMTBL IRGen.TheSema->TheASTContext->Symtbl
#define IRBuilder IRGen.IRBuilder
#define Module IRGen.Module
#define Context IRGen.Context

class ExprIRGenVisitor : public ast::ExprVisitor {
public:
    ir::LLVMIRGen& IRGen;
    llvm::Value* RetVal;
    llvm::AllocaInst* Local;
    llvm::Value* Self;
    ExprIRGenVisitor(ir::LLVMIRGen& iRGen, llvm::AllocaInst* local, llvm::Value* self) 
        : IRGen(iRGen), Local(local), Self(self) { 
    }
public:
void operator()(ast::Expr &expr, ast::ExprInt &rawExpr) {
    auto IntS = SYMTBL.getInt();
    auto retval = llvm::ConstantStruct::get(
        IRGen.FatPointerTy, {
            IRGen.getVTableConstant(IntS),
            llvm::ConstantExpr::getIntToPtr(
                llvm::ConstantInt::get(IRGen.BuiltIntTy, 
                    llvm::APInt(64, rawExpr.Val, true)), 
                IRGen.HeapObjRefTy)
        }
    );
    RetVal = retval;
}
 
void operator()(ast::Expr &expr, ast::ExprFloat &rawExpr) {
    auto FloatS = SYMTBL.getFloat();
    auto retval = llvm::ConstantStruct::get(
        IRGen.FatPointerTy, {
            IRGen.getVTableConstant(FloatS),
            llvm::ConstantExpr::getIntToPtr(
                llvm::ConstantExpr::getBitCast(
                    llvm::ConstantFP::get(IRGen.BuiltFloatTy, 
                        llvm::APFloat(rawExpr.Val)), 
                    IRGen.BuiltIntTy), 
                IRGen.HeapObjRefTy)
        }
    );
    RetVal = retval;
}
 
void operator()(ast::Expr &expr, ast::ExprBool &rawExpr) {
    auto BoolS = SYMTBL.getFloat();
    auto retval = llvm::ConstantStruct::get(
        IRGen.FatPointerTy, {
            IRGen.getVTableConstant(BoolS),
            llvm::ConstantExpr::getIntToPtr(
                llvm::ConstantInt::get(IRGen.BuiltIntTy, 
                    llvm::APInt(64, static_cast<int>(rawExpr.Val), true)), 
                IRGen.HeapObjRefTy)
        }
    );
    RetVal = retval;
}
 
void operator()(ast::Expr &expr, ast::ExprString &rawExpr) {
    // TODO: ExprString
}

llvm::Value* getVarPointer(sema::SemaScope* scope, ast::Symbol varName, llvm::StringRef name = "") {
    llvm::Value* var ;
    int Offset = scope->findVariable(varName).Offset;
    if (scope->getKind() == sema::SemaScope::SK_Class) {
        auto selfHeapObj = IRBuilder.CreateExtractValue(Self, {1}, "self.heapObj");
        var = IRBuilder.CreateGEP(
            IRGen.HeapObjTy, selfHeapObj, {CONSTINT32(0), CONSTINT32(Offset)});
    } else {
        var = IRBuilder.CreateGEP(
            IRGen.FatPointerTy, Local, CONSTINT32(Offset), name);
    }
    return var;
}

void operator()(ast::Expr &expr, ast::ExprSymbol &rawExpr) {
    auto annot = static_cast<sema::ExprSymbolAnnotation*>(expr.Annotation);
    auto var = getVarPointer(annot->ScopeRef, rawExpr.TheSymbol, rawExpr.TheSymbol.getName());
    RetVal = IRBuilder.CreateLoad(IRGen.FatPointerTy, var, SYMCONCAT(rawExpr.TheSymbol, ".val"));
}
 
void operator()(ast::Expr &expr, ast::ExprAssign &rawExpr) {
    auto annot = static_cast<sema::ExprAssignAnnotation*>(expr.Annotation);
    rawExpr.Value.accept(*this);
    auto var = getVarPointer(annot->ScopeRef, rawExpr.Variable, rawExpr.Variable.getName());
    IRBuilder.CreateStore(RetVal, var);
}

llvm::Value* createCall(llvm::Function* staticF,
                           int methodOffset,
                           ast::Expr callee, 
                           llvm::MutableArrayRef<ast::Expr> args,
                           bool isStatic) {
    callee.accept(*this);
    auto CalleeFP = RetVal;
    ValueList agrsVal; agrsVal.reserve(args.size() + 1);
    agrsVal.push_back(CalleeFP);
    for(auto& arg : args) {
        arg.accept(*this);
        agrsVal.push_back(RetVal);
    }
    if (isStatic) {
        return IRBuilder.CreateCall(staticF, agrsVal);
    } else {
        auto vtable = IRBuilder.CreateExtractValue(CalleeFP, {0});
        auto dynF = IRBuilder.CreateGEP(IRGen.VTableTy, vtable,{
            CONSTINT32(0), CONSTINT32(1), 
            CONSTINT32(methodOffset)
            });
        auto staticFT = staticF->getFunctionType();
        dynF = IRBuilder.CreateBitCast(dynF, staticFT->getPointerTo()->getPointerTo());
        dynF = IRBuilder.CreateLoad(staticFT->getPointerTo(), dynF);
        return IRBuilder.CreateCall(staticFT, dynF, agrsVal);
    }
}

void operator()(ast::Expr &expr, ast::ExprDispatch &rawExpr) {
    auto annot = static_cast<sema::ExprDispatchAnnotation*>(expr.Annotation);
    auto methodAnnot = annot->StaticMethodRef->Annotation;
    auto staticF = IRGen.getMethod(annot->StaticMethodClassRef->Name, rawExpr.Method);
    bool canStatic =  annot->StaticMethodClassRef->IsFinal;
    RetVal = this->createCall(
        staticF, methodAnnot->MethodOffset,
        rawExpr.Callee, rawExpr.Args, canStatic
    );
}
 
void operator()(ast::Expr &expr, ast::ExprStaticDispatch &rawExpr) {
    auto annot = static_cast<sema::ExprStaticDispatchAnnotation*>(expr.Annotation);
    auto methodAnnot = annot->StaticMethodRef->Annotation;
    auto staticF = IRGen.getMethod(annot->StaticMethodClassRef->Name, rawExpr.Method);
    RetVal = this->createCall(
        staticF, methodAnnot->MethodOffset,
        rawExpr.Callee, rawExpr.Args, true
    );
}
 
void operator()(ast::Expr &expr, ast::ExprCond &rawExpr) {
    auto entryBB = CREATEBB("if.entry");
    auto thenBB = CREATEBB("if.then");
    auto elseBB = CREATEBB("if.else");
    auto mergeBB = CREATEBB("if.merge");
    // entry
    IRBuilder.CreateBr(entryBB);
    IRBuilder.SetInsertPoint(entryBB);
    rawExpr.Cond.accept(*this);
    auto cond = RetVal;
    auto condbool = IRBuilder.CreateTrunc(
        IRBuilder.CreatePtrToInt(
            IRBuilder.CreateExtractValue(
                cond, {1}, "cond"), 
            IRGen.BuiltIntTy), 
        IRGen.BuiltBoolTy, "cond.bool");
    IRBuilder.CreateCondBr(condbool, thenBB, elseBB);
    // then
    IRBuilder.SetInsertPoint(thenBB);
    rawExpr.ThenBranch.accept(*this); 
    auto thenval = RetVal;
    IRBuilder.CreateBr(mergeBB);
    thenBB = IRBuilder.GetInsertBlock();
    // else
    IRBuilder.SetInsertPoint(elseBB);
    rawExpr.ElseBranch.accept(*this); 
    auto elseval = RetVal;
    elseBB = IRBuilder.GetInsertBlock();
    IRBuilder.CreateBr(mergeBB);
    // merge
    IRBuilder.SetInsertPoint(mergeBB);
    auto phi = IRBuilder.CreatePHI(IRGen.FatPointerTy, 2, "if.val");
    phi->addIncoming(thenval, thenBB);
    phi->addIncoming(elseval, elseBB);
    RetVal = phi;
}
 
void operator()(ast::Expr &expr, ast::ExprLoop &rawExpr) {
    auto entryBB = CREATEBB("loop.entry");
    auto bodyBB = CREATEBB("loop.body");
    auto exitBB = CREATEBB("loop.exit");
    // entry
    IRBuilder.CreateBr(entryBB);
    IRBuilder.SetInsertPoint(entryBB);
    rawExpr.Cond.accept(*this);
    auto cond = RetVal;
    auto condbool = IRBuilder.CreateTrunc(
        IRBuilder.CreatePtrToInt(
            IRBuilder.CreateExtractValue(
                cond, {1}, "cond"), 
            IRGen.BuiltIntTy), 
        IRGen.BuiltBoolTy, "cond.bool");
    entryBB = IRBuilder.GetInsertBlock();
    IRBuilder.CreateCondBr(condbool, bodyBB, exitBB);
    // body
    IRBuilder.SetInsertPoint(bodyBB);
    rawExpr.LoopBody.accept(*this);
    auto body = RetVal;
    rawExpr.Cond.accept(*this);
    cond = RetVal;
    condbool = IRBuilder.CreateTrunc(
        IRBuilder.CreatePtrToInt(
            IRBuilder.CreateExtractValue(
                cond, {1}, "cond"), 
            IRGen.BuiltIntTy), 
        IRGen.BuiltBoolTy, "cond.bool");
    IRBuilder.CreateCondBr(condbool, bodyBB, exitBB);
    bodyBB = IRBuilder.GetInsertBlock();
    // exit
    IRBuilder.SetInsertPoint(exitBB);
    auto phi = IRBuilder.CreatePHI(IRGen.FatPointerTy, 2, "loop.val");
    phi->addIncoming(getNull(), entryBB);
    phi->addIncoming(body, bodyBB);
    RetVal = phi;
}
 
void operator()(ast::Expr &expr, ast::ExprCase &rawExpr) {
    // TODO: case
}
 
void operator()(ast::Expr &expr, ast::ExprBlock &rawExpr) {
    for(auto& e : rawExpr.Exprs) {
        e.accept(*this);
    }
}
 
void operator()(ast::Expr &expr, ast::ExprLet &rawExpr) {
    auto annot = static_cast<sema::ExprLetAnnotation*>(expr.Annotation);
    for(auto& v : rawExpr.InitVariables) {
        if (v.Init.has_value()) {
            auto var = getVarPointer(&annot->LocalScope, v.Formal.Name, "let.init");
            v.Init.value().accept(*this);
            IRBuilder.CreateStore(RetVal, var);
        }
    }
    rawExpr.LetBody.accept(*this);
}
 
void operator()(ast::Expr &expr, ast::ExprNew &rawExpr) {
    auto newMethod = IRGen.getMethod(rawExpr.Type, SYMTBL.getNewMethod());
    RetVal = IRBuilder.CreateCall(newMethod, {}, SYMCONCAT(rawExpr.Type, ".val"));
}
 
void operator()(ast::Expr &expr, ast::ExprSelf &rawExpr) {
    RetVal = Self;
}

llvm::Value* getNull() {
    return llvm::ConstantStruct::get(IRGen.FatPointerTy, {
        IRGen.getVTableConstant(SYMTBL.getNullType()), 
        llvm::ConstantExpr::getIntToPtr(llvm::ConstantInt::get(Context, llvm::APInt(64, 0)), IRGen.HeapObjRefTy)});
};
 
void operator()(ast::Expr &expr, ast::ExprNull &rawExpr) {
    RetVal = this->getNull();
}
 
void operator()(ast::Expr &expr, ast::ExprArithB &rawExpr) {
    auto annot = static_cast<sema::ExprArithBAnnotation*>(expr.Annotation);
    auto methodAnnot = annot->StaticMethodRef->Annotation;
    auto staticF = IRGen.getMethod(
        annot->StaticMethodClassRef->Name, 
        SYMTBL.get(rawExpr.getFuncName()));
    bool canStatic =  annot->StaticMethodClassRef->IsFinal;
    RetVal = this->createCall(
        staticF, methodAnnot->MethodOffset,
        rawExpr.Left, rawExpr.Right, canStatic
    );
}
 
void operator()(ast::Expr &expr, ast::ExprArithU &rawExpr) {
    auto annot = static_cast<sema::ExprArithBAnnotation*>(expr.Annotation);
    auto methodAnnot = annot->StaticMethodRef->Annotation;
    auto staticF = IRGen.getMethod(
        annot->StaticMethodClassRef->Name, 
        SYMTBL.get(rawExpr.getFuncName()));
    bool canStatic =  annot->StaticMethodClassRef->IsFinal;
    RetVal = this->createCall(
        staticF, methodAnnot->MethodOffset,
        rawExpr.Operand, {}, canStatic
    );
}
};

}
}

llvm::Value* ir::LLVMIRGen::emitExpr(ast::Expr expr, llvm::Value* self, llvm::AllocaInst* local) {
    ExprIRGenVisitor v(*this, local, self);
    expr.accept(v);
    return v.RetVal; //TODO
}
#include "gcool/LLVMIRGen/LLVMIRGen.h"
#include "gcool/AST/Expr.h"

using namespace gcool;

#define ASTCONTEXT IRGen.TheSema->TheASTContext
#define SYMTBL IRGen.TheSema->TheASTContext->Symtbl
#define IRBuilder IRGen.IRBuilder
#define Module IRGen.Module
#define Context IRGen.Context

#define CONSTINT32(val) llvm::ConstantInt::get(Context, llvm::APInt(32, val))

namespace gcool {
namespace ir {

class ExprIRGenVisitor : public ast::ExprVisitor {
public:
    ir::LLVMIRGen& IRGen;
    llvm::Value* RetVal;
    ExprIRGenVisitor(ir::LLVMIRGen& iRGen) : IRGen(iRGen) {}
public:
void operator()(ast::Expr &expr, ast::ExprInt &rawExpr) {
    auto IntS = SYMTBL.getInt();
    auto retval = llvm::ConstantStruct::get(
        IRGen.FatPointerTy, {
            IRGen.getVTableConstant(IntS),
            llvm::ConstantExpr::getIntToPtr(
                llvm::ConstantInt::get(IRGen.BuiltIntTy, 
                    llvm::APInt(64, rawExpr.Val, true)), 
                IRGen.ObjectRefTy)
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
                IRGen.ObjectRefTy)
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
                IRGen.ObjectRefTy)
        }
    );
    RetVal = retval;
}
 
void operator()(ast::Expr &expr, ast::ExprString &rawExpr) {

}
 
void operator()(ast::Expr &expr, ast::ExprSymbol &rawExpr) {

}
 
void operator()(ast::Expr &expr, ast::ExprAssign &rawExpr) {

}
 
void operator()(ast::Expr &expr, ast::ExprDispatch &rawExpr) {
    auto annot = static_cast<sema::ExprDispatchAnnotation*>(expr.Annotation);
    auto methodAnnot = annot->MethodRef->Annotation;
    rawExpr.Callee.accept(*this);
    auto CalleeFP = RetVal;
    ValueList agrsVal; agrsVal.reserve(rawExpr.Args.size() + 1);
    agrsVal.push_back(CalleeFP);
    for(auto& args : rawExpr.Args) {
        args.accept(*this);
        agrsVal.push_back(RetVal);
    }
    auto vtable = IRBuilder.CreateExtractValue(CalleeFP, {0});
    auto dynF = IRBuilder.CreateGEP(IRGen.VTableTy, vtable,{
        CONSTINT32(0), CONSTINT32(1), 
        CONSTINT32(methodAnnot->MethodOffset)
        });
    auto staticF = IRGen.getMethod(methodAnnot->InClass->Name, rawExpr.Method);
    auto staticFT = staticF->getFunctionType();
    dynF = IRBuilder.CreateBitCast(dynF, staticFT->getPointerTo()->getPointerTo());
    dynF = IRBuilder.CreateLoad(staticFT->getPointerTo(), dynF);
    RetVal = IRBuilder.CreateCall(staticFT, dynF, agrsVal);
}
 
void operator()(ast::Expr &expr, ast::ExprStaticDispatch &rawExpr) {

}
 
void operator()(ast::Expr &expr, ast::ExprCond &rawExpr) {

}
 
void operator()(ast::Expr &expr, ast::ExprLoop &rawExpr) {

}
 
void operator()(ast::Expr &expr, ast::ExprCase &rawExpr) {

}
 
void operator()(ast::Expr &expr, ast::ExprBlock &rawExpr) {

}
 
void operator()(ast::Expr &expr, ast::ExprLet &rawExpr) {

}
 
void operator()(ast::Expr &expr, ast::ExprNew &rawExpr) {

}
 
void operator()(ast::Expr &expr, ast::ExprSelf &rawExpr) {

}
 
void operator()(ast::Expr &expr, ast::ExprNull &rawExpr) {

}
 
void operator()(ast::Expr &expr, ast::ExprArithB &rawExpr) {

}
 
void operator()(ast::Expr &expr, ast::ExprArithU &rawExpr) {

}
};

}
}

llvm::Value* ir::LLVMIRGen::emitExpr(ast::Expr expr) {
    ExprIRGenVisitor v(*this);
    expr.accept(v);
    return v.RetVal; //TODO
}
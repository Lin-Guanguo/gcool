#include "gcool/LLVMIRGen/LLVMIRGen.h"
#include "gcool/AST/Expr.h"

using namespace gcool;

#define ASTCONTEXT IRGen.TheSema->TheASTContext
#define SYMTBL IRGen.TheSema->TheASTContext->Symtbl
#define IRBuilder IRGen.IRBuilder
#define Module IRGen.Module
#define Context IRGen.Context

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
    auto retval = IRBuilder.CreateInsertValue(
        llvm::UndefValue::get(
            IRGen.getFatPointer(IntS)), 
        IRGen.getVTableConstant(IntS), {0});
    retval = IRBuilder.CreateInsertValue(retval,
        IRBuilder.CreateIntToPtr(
            llvm::ConstantInt::get(IRGen.BuiltIntTy, 
                llvm::APInt(64, rawExpr.Val, true)), 
            IRGen.ObjectRefTy), 
        {1});
    RetVal = retval;
}
 
void operator()(ast::Expr &expr, ast::ExprFloat &rawExpr) {
    auto FloatS = SYMTBL.getFloat();
    auto retval = IRBuilder.CreateInsertValue(
        llvm::UndefValue::get(
            IRGen.getFatPointer(FloatS)), 
        IRGen.getVTableConstant(FloatS), {0});
    retval = IRBuilder.CreateInsertValue(retval, 
        IRBuilder.CreateIntToPtr(
            IRBuilder.CreateBitCast(
                llvm::ConstantFP::get(IRGen.BuiltFloatTy, 
                    llvm::APFloat(rawExpr.Val)), 
                IRGen.BuiltIntTy), 
            IRGen.ObjectRefTy), 
        {1});
    RetVal = retval;
}
 
void operator()(ast::Expr &expr, ast::ExprBool &rawExpr) {

}
 
void operator()(ast::Expr &expr, ast::ExprString &rawExpr) {

}
 
void operator()(ast::Expr &expr, ast::ExprSymbol &rawExpr) {

}
 
void operator()(ast::Expr &expr, ast::ExprAssign &rawExpr) {

}
 
void operator()(ast::Expr &expr, ast::ExprDispatch &rawExpr) {

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
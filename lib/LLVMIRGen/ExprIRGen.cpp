#include "gcool/LLVMIRGen/LLVMIRGen.h"
#include "gcool/AST/Expr.h"

using namespace gcool;

#define ASTCONTEXT TheSema->TheASTContext
#define SYMTBL TheSema->TheASTContext->Symtbl

namespace {

class ExprIRGenVisitor : public ast::ExprVisitor {
public:
    ir::LLVMIRGen& IRGen;
    llvm::Value* RetVal;
    ExprIRGenVisitor(ir::LLVMIRGen& iRGen) : IRGen(iRGen) {}
public:
void operator()(ast::Expr &expr, ast::ExprInt &rawExpr) {

}
 
void operator()(ast::Expr &expr, ast::ExprFloat &rawExpr) {

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

llvm::Value* ir::LLVMIRGen::emitExpr(ast::Expr expr) {
    ExprIRGenVisitor v(*this);
    expr.accept(v);
    return v.RetVal; //TODO
}
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/ADT/STLExtras.h"
#include <iostream>
#include "gcool/AST/Expr.h"


int main(int argc, char** argv) 
{
    using namespace gcool::ast;
    ExprAllocator alloc;
    Expr e1 = alloc.allocExpr(new ExprInt(1));
    Expr e2 = alloc.allocExpr(new ExprInt(1));
    Expr e3 = alloc.allocExpr(new ExprFloat(1));
    Expr e4 = alloc.allocExpr(new ExprFloat(1));
    llvm::outs() << (e1 == e1); 
    llvm::outs() << (e1 == e2); 
    llvm::outs() << (e2 == e3); 
    llvm::outs() << (e3 == e4); 
    
}
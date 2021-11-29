#pragma once
#include "gcool/AST/AST.h"
#include "gcool/Sema/Sema.h"

namespace llvm {
    class raw_ostream;
}

namespace gcool {
namespace pretty {

class ASTPrinter {
public:
    int Indent = 0;
    int IndentSpace = 2;
    bool IsPrintBuiltin = false;
public:
    void printIndent(llvm::raw_ostream& os);

    void printAST(llvm::raw_ostream& os, sema::Sema& sema);
    void printErrorList(llvm::raw_ostream& os, sema::ErrorList& errorlist);
    void printSymbolTable(llvm::raw_ostream& os, ast::SymbolTable& TheSymbolTable);
    void printClassList(llvm::raw_ostream& os, ast::ClassList& TheClassList);
    void printClass(llvm::raw_ostream& os, ast::Class& TheClass);
    void printAttr(llvm::raw_ostream& os, ast::AttrFeature& TheAttr);
    void printMethod(llvm::raw_ostream& os, ast::MethodFeature& TheMethod);
    void printScope(llvm::raw_ostream& os, sema::SemaScope* scope);
    void printExpr(llvm::raw_ostream& os, ast::Expr& expr);


};

}
}

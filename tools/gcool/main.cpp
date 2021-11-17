#include <iostream>
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/ADT/STLExtras.h"
#include "gcool/AST/Expr.h"
#include "gcool/AST/AST.h"
#include "gcool/Parser/Parser.h"
#include "gcool/Lexer/Lexer.h"
#include "gcool/Sema/Sema.h"
#include "gcool/Basic/Diag.h"
#include "llvm/Support/FormatVariadic.h"

using namespace gcool;
using namespace gcool::ast;

int main(int argc, char** argv) 
{

    const char* input = 
    R"(
        class Main {};
        class Main {};
        class Main {};
        class Loop1 inherits Loop2 {};
        class Loop2 inherits Loop1 {};
    )";

    ASTContext context;
    yyscan_t scanner;
    yylex_init(&scanner);
    yy_scan_string(input, scanner);
    Parser parser{scanner, &context};
    parser.parse();

    sema::Sema theSema(&context);
    theSema.checkAll();
    for (auto& s : theSema.TheErrorList){
        llvm::outs() << s << "\n";
    }
}
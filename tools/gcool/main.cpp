#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/ADT/STLExtras.h"
#include <iostream>
#include "gcool/AST/Expr.h"
#include "gcool/AST/AST.h"
#include "gcool/Parser/Parser.h"
#include "gcool/Lexer/Lexer.h"

using namespace gcool;
using namespace gcool::ast;

void TestHelper(const char* input, ast::ASTContext& context, ast::ClassList& expect) {
    yyscan_t scanner;
    yylex_init(&scanner);
    yy_scan_string(input, scanner);
    Parser parser{scanner, &context};
    parser.parse();
    llvm::outs() << (expect == context.Classes);
}

void test() {
    ast::ASTContext context;
    const char* input = 
    R"(
        class Main
        {

        };
        class help_class{ };
    )";

    ast::ClassList expect{
        Class{ context.Symtbl.get("Main") },
        Class{ context.Symtbl.get("help_class") }
    };
    TestHelper(input, context, expect);
}

int main(int argc, char** argv) 
{
    test();
    
}
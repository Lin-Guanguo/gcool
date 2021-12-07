#include <stdio.h>
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
#include "gcool/PrettyPrinter/ASTPrinter.h"
#include "gcool/LLVMIRGen/LLVMIRGen.h"

using namespace gcool;

int main(int argc, char** argv) 
{
    if (argc < 2) {
        printf("gcool: Usage gcool [file.cl]+\n");
        return -1;
    }


    yyscan_t scanner;
    yylex_init(&scanner);
    for (int i = 1; i < argc; ++i) {
        auto filename = argv[i];
        printf("start compile %s\n", filename);
        auto file = fopen(filename, "r");
        if (file == NULL) {
            printf("open file %s error\n", filename);
            continue;
        }
        // lexer
        yyrestart(file, scanner);

        // parser
        ast::ASTContext context;
        Parser parser{scanner, &context};
        parser.parse();

        sema::Sema sema(&context);
        sema.checkAll();
        

    }
}
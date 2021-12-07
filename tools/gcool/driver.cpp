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
        fprintf(stderr, "gcool: Usage gcool [file.cl]+\n");
        return -1;
    }

    bool fileError = false;
    yyscan_t scanner;
    yylex_init(&scanner);
    ast::ASTContext context;
    Parser parser{scanner, &context};
    for (int i = 1; i < argc; ++i) {
        auto filename = argv[i];
        fprintf(stderr, "start compile %s\n", filename);
        auto file = fopen(filename, "r");
        if (file == NULL) {
            fprintf(stderr, "open file %s error\n", filename);
            fileError = true;
            continue;
        }
        // lexer
        yyrestart(file, scanner);

        // parser
        parser.parse();
        if (context.HasParserError) {
            fileError = true;
            fprintf(stderr, "Parse file %s error\n", filename);
            continue;
        }
    }
    if (fileError)
        return -1;

    // sema
    sema::Sema sema(&context);
    sema.checkAll();
    if (!sema.TheErrorList.empty()) {
        fprintf(stderr, "Semantic analysis error\n");
        for (auto& e : sema.TheErrorList) 
            llvm::errs() << e << "\n";
        return -1;
    }

    // print AST
    pretty::ASTPrinter printer;
    printer.printAST(llvm::errs(), sema);

    // code gen
    ir::LLVMIRGen irgen(&sema);
    irgen.emitLLVMIR();
    irgen.print(llvm::outs());
}
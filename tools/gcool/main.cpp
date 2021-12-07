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
#include "gcool/PrettyPrinter/ASTPrinter.h"
#include "gcool/LLVMIRGen/LLVMIRGen.h"

using namespace gcool;
using namespace gcool::ast;
using namespace gcool::sema;

using ErrorKindList = std::vector<gcool::basic::Diag::DiagKind>;

void checkError(const char* input, const ErrorKindList& errorList, bool debugPrint) {
    yyscan_t scanner;
    yylex_init(&scanner);
    yy_scan_string(input, scanner);

    ast::ASTContext context;
    Parser parser{scanner, &context};
    parser.parse();

    Sema sema(&context);
    sema.checkAll();
    
    pretty::ASTPrinter printer;
    printer.IsPrintBuiltin = true;
    printer.printAST(llvm::errs(), sema);

    if (debugPrint) {
        for(auto e : sema.TheErrorList) {
            std::cerr << e.DiagKindName[e.TheDiagKind] << " : " << e.AdditionalMsg << "\n";
        }
    }

    ir::LLVMIRGen irgen(&sema);
    irgen.emitLLVMIR();
    irgen.print(llvm::outs());

   

    // EXPECT_EQ(sema.TheErrorList.size(), errorList.size());
    // for(int i = 0; i < errorList.size(); ++i) {
    //     EXPECT_EQ(sema.TheErrorList[i].TheDiagKind, errorList[i]);
    // }
}


int main(int argc, char** argv) 
{
    //llvm::outs() << "pointer size " << sizeof(void*) << "\n";
    const char* input = 
    R"(
        class Main {
            c : Int <- 10;
            d : Int <- 10;
            b : Float <- 20.0;
            main() : Int {
                (new Main4).hello3(null, 6) + (new Main4).hello3(3, 9)
            };
        };

        class Main4 inherits Main2 {
            c : Float <- 20.2;
            d : Int <- 5;
            hello(i : Int, i2 : Int, b : Bool) : Int {
                if b then
                    while d.oplt(10) loop {
                        d <- d.opadd(1);
                        i <- i.opadd(1);
                    }
                    pool
                else
                    i.opadd(i2)
                fi
            };

            hello2(i : Int) : Int {
                let count : Int <- 1 in
                    while not count.opgt(10) loop {
                        count <- count + 2;
                        i <- i + 1;
                    } pool
            };

            hello3(i : Int, i2 : Int) : Int {
                if isvoid i then
                    i2
                else
                    i
                fi
            };
        };

        class Main2 inherits Main {
            c : Float <- 9.02;
        };
    )";
    ErrorKindList errorList = {
    };
    checkError(input, errorList, true);

}
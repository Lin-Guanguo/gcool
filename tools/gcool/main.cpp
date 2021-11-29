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
    //printer.printAST(llvm::outs(), sema);

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
            c : Int <- 10.opadd(2);
            b : Float <- 20.0;
            main() : Int {
                152
            };
        };

        class Main4 inherits Main2 {
            c : Float <- 20.2;
            hello(f : Float, i : Int, b : Bool) : Float {
                10.2
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
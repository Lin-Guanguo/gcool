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

    if (debugPrint) {
        for(auto e : sema.TheErrorList) {
            std::cerr << e.DiagKindName[e.TheDiagKind] << " : " << e.AdditionalMsg << "\n";
        }
    }

    // EXPECT_EQ(sema.TheErrorList.size(), errorList.size());
    // for(int i = 0; i < errorList.size(); ++i) {
    //     EXPECT_EQ(sema.TheErrorList[i].TheDiagKind, errorList[i]);
    // }
}

int main(int argc, char** argv) 
{
    const char* input = 
    R"(
        class Main {
            a : WrongClass;
            b : Int <- true;
            c : Bool <- false;
            d : Float <- 10.2;
            e : Int <- 10;
        };
    )";
    ErrorKindList errorList = {

    };
    checkError(input, errorList, true);
}
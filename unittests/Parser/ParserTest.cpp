#include "gtest/gtest.h"
#include "gcool/Lexer/Lexer.h"
#include "gcool/Parser/Parser.h"
#include "gcool/AST/Expr.h"
#include <vector>

using namespace gcool;
using namespace gcool::ast;

void TestHelper(const char* input, ast::ASTContext& context, ast::ClassList& expect) {
    yyscan_t scanner;
    yylex_init(&scanner);
    yy_scan_string(input, scanner);
    Parser parser{scanner, &context};
    parser.parse();
    EXPECT_TRUE(expect == context.Classes);
}

TEST(ParserTest, GCoolClassTest) {
    ast::ASTContext context;
    const char* input = 
    R"(
        class Main
        {

        };
        class help_class{ };
    )";

    ClassList expect{
        Class{ context.Symtbl.get("Main") },
        Class{ context.Symtbl.get("help_class") }
    };
    TestHelper(input, context, expect);
}
#include "gtest/gtest.h"
#include "gcool/Lexer/Lexer.h"
#include "gcool/Parser/Parser.h"
#include "gcool/AST/Expr.h"
#include <vector>

using namespace gcool;
using namespace gcool::ast;
#define ALLOC_EXPR(Init) context.ExprAlloc.allocExpr(new Init)

void TestHelper(const char* input, ast::ASTContext& context, ast::ClassList& expect) {
    yyscan_t scanner;
    yylex_init(&scanner);
    yy_scan_string(input, scanner);
    Parser parser{scanner, &context};
    parser.parse();
    EXPECT_TRUE(expect == context.Classes);
}

TEST(ParserTest, EqOperatorTest)
{
    ast::ASTContext context;
    EXPECT_FALSE(ALLOC_EXPR(ExprInt(10)) == ALLOC_EXPR(ExprInt(12)));
    EXPECT_FALSE(ALLOC_EXPR(ExprInt(10)) == ALLOC_EXPR(ExprFloat(10.2)));
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
        Class{ context.Symtbl.get("Main"), context.Symtbl.getObject() },
        Class{ context.Symtbl.get("help_class"), context.Symtbl.getObject() }
    };
    TestHelper(input, context, expect);
}

TEST(ParserTest, AttrTest) {
    ast::ASTContext context;
    const char* input = 
    R"(
        class Main
        {
            i1 : Int;
            i2 : Int <- 10;
        };
    )";
    ClassList expect{
        Class{ context.Symtbl.get("Main"), 
            AttrList{
                AttrFeature{ 
                    FormalDecl{context.Symtbl.get("i1"), context.Symtbl.getInt()},
                    OptionalExpr{} 
                },
                AttrFeature{
                    FormalDecl{context.Symtbl.get("i2"), context.Symtbl.getInt()},
                    OptionalExpr{ALLOC_EXPR(ExprInt(10))} 
                }
            },
            MethodList{},
            context.Symtbl.getObject()
        }
    };
    TestHelper(input, context, expect);
}

TEST(ParserTest, MethodTest) {
    ast::ASTContext context;
    const char* input = 
    R"(
        class Main
        {
            main() : Int {
                10
            };
        };
    )";
    ClassList expect{
        Class{ context.Symtbl.get("Main"), 
            AttrList{},
            MethodList{
                MethodFeature{
                    context.Symtbl.get("main"),
                    context.Symtbl.getInt(),
                    FormalList{},
                    ALLOC_EXPR(ExprInt(10))
                }
            },
            context.Symtbl.getObject()
        }
    };
    TestHelper(input, context, expect);
}

TEST(ParserTest, ConstTest) {
    ast::ASTContext context;
    const char* input = 
    R"(
        class Main
        {
            i1 : Int <- 10;
            f1 : Float <- 10.2;
            b1 : Bool <- true;
            b2 : Bool <- false;
            s1 : String <- "hello world\n";
            s2 : String <- s1;
        };
    )";
    ClassList expect{
        Class{ context.Symtbl.get("Main"), 
            AttrList{
                AttrFeature{ 
                    FormalDecl{context.Symtbl.get("i1"), context.Symtbl.getInt()},
                    OptionalExpr{ALLOC_EXPR(ExprInt(10))} 
                },
                AttrFeature{
                    FormalDecl{context.Symtbl.get("f1"), context.Symtbl.getFloat()},
                    OptionalExpr{ALLOC_EXPR(ExprFloat(10.2))} 
                },
                AttrFeature{
                    FormalDecl{context.Symtbl.get("b1"), context.Symtbl.getBool()},
                    OptionalExpr{ALLOC_EXPR(ExprBool(true))} 
                },
                AttrFeature{
                    FormalDecl{context.Symtbl.get("b2"), context.Symtbl.getBool()},
                    OptionalExpr{ALLOC_EXPR(ExprBool(false))} 
                },
                AttrFeature{
                    FormalDecl{context.Symtbl.get("s1"), context.Symtbl.getString()},
                    OptionalExpr{ALLOC_EXPR(ExprString("hello world\n"))} 
                },
                AttrFeature{
                    FormalDecl{context.Symtbl.get("s2"), context.Symtbl.getString()},
                    OptionalExpr{ALLOC_EXPR(ExprSymbol(context.Symtbl.get("s1")))} 
                }
            },
            MethodList{},
            context.Symtbl.getObject()
        }
    };
    TestHelper(input, context, expect);
}
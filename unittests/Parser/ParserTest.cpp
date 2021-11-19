#include "gtest/gtest.h"
#include "gcool/Lexer/Lexer.h"
#include "gcool/Parser/Parser.h"
#include "gcool/AST/Expr.h"
#include <vector>

using namespace gcool;
using namespace gcool::ast;
#define ALLOC_EXPR(Init) context.ExprAlloc.allocExpr(new Init)
#define SYMTBL context.Symtbl

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
        Class{ SYMTBL.get("Main"), SYMTBL.getObject() },
        Class{ SYMTBL.get("help_class"), SYMTBL.getObject() }
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
        Class{ SYMTBL.get("Main"), 
            AttrList{
                AttrFeature{ 
                    FormalDecl{SYMTBL.get("i1"), SYMTBL.getInt()},
                    OptionalExpr{} 
                },
                AttrFeature{
                    FormalDecl{SYMTBL.get("i2"), SYMTBL.getInt()},
                    OptionalExpr{ALLOC_EXPR(ExprInt(10))} 
                }
            },
            MethodList{},
            SYMTBL.getObject()
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
        Class{ SYMTBL.get("Main"), 
            AttrList{},
            MethodList{
                MethodFeature{
                    SYMTBL.get("main"),
                    SYMTBL.getInt(),
                    FormalList{},
                    ALLOC_EXPR(ExprInt(10))
                }
            },
            SYMTBL.getObject()
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
        Class{ SYMTBL.get("Main"), 
            AttrList{
                AttrFeature{ 
                    FormalDecl{SYMTBL.get("i1"), SYMTBL.getInt()},
                    OptionalExpr{ALLOC_EXPR(ExprInt(10))} 
                },
                AttrFeature{
                    FormalDecl{SYMTBL.get("f1"), SYMTBL.getFloat()},
                    OptionalExpr{ALLOC_EXPR(ExprFloat(10.2))} 
                },
                AttrFeature{
                    FormalDecl{SYMTBL.get("b1"), SYMTBL.getBool()},
                    OptionalExpr{ALLOC_EXPR(ExprBool(true))} 
                },
                AttrFeature{
                    FormalDecl{SYMTBL.get("b2"), SYMTBL.getBool()},
                    OptionalExpr{ALLOC_EXPR(ExprBool(false))} 
                },
                AttrFeature{
                    FormalDecl{SYMTBL.get("s1"), SYMTBL.getString()},
                    OptionalExpr{ALLOC_EXPR(ExprString("hello world\n"))} 
                },
                AttrFeature{
                    FormalDecl{SYMTBL.get("s2"), SYMTBL.getString()},
                    OptionalExpr{ALLOC_EXPR(ExprSymbol(SYMTBL.get("s1")))} 
                }
            },
            MethodList{},
            SYMTBL.getObject()
        }
    };
    TestHelper(input, context, expect);
}

TEST(ParserTest, ParamsTest) {
    ast::ASTContext context;
    const char* input = 
    R"(
        class Main
        {
            main(i1 : Int, f1 : Float) : Int {
                10
            };
        };
    )";
    ClassList expect{
        Class{ SYMTBL.get("Main"), 
            AttrList{},
            MethodList{
                MethodFeature{
                    SYMTBL.get("main"),
                    SYMTBL.getInt(),
                    FormalList{ 
                        FormalDecl{SYMTBL.get("i1"), SYMTBL.getInt()}, 
                        FormalDecl{SYMTBL.get("f1"), SYMTBL.getFloat()}
                    },
                    ALLOC_EXPR(ExprInt(10))
                }
            },
            SYMTBL.getObject()
        }
    };
    TestHelper(input, context, expect);
}

TEST(ParserTest, ExprNewTest) {
    ast::ASTContext context;
    const char* input = 
    R"(
        class Main
        {
            i1 : Int <- new Int;
        };
    )";
    ClassList expect{
        Class{ SYMTBL.get("Main"), 
            AttrList{
                AttrFeature{
                    FormalDecl{SYMTBL.get("i1"), SYMTBL.getInt()},
                    OptionalExpr{ALLOC_EXPR(ExprNew(SYMTBL.getInt()))} 
                }
            },
            MethodList{},
            SYMTBL.getObject()
        }
    };
    TestHelper(input, context, expect);
}

TEST(ParserTest, ExprArithUTest) {
    ast::ASTContext context;
    const char* input = 
    R"(
        class Main
        {
            b1 : Bool <- isvoid Symbol;
            b2 : Bool <- not Symbol;
        };
    )";
    ClassList expect{
        Class{ SYMTBL.get("Main"), 
            AttrList{
                AttrFeature{
                    FormalDecl{SYMTBL.get("b1"), SYMTBL.getBool()},
                    OptionalExpr{ALLOC_EXPR(ExprArithU( 
                        ALLOC_EXPR(ExprSymbol(SYMTBL.get("Symbol"))), 
                        ExprArithU::OP_ISVOID))
                    } 
                },
                AttrFeature{
                    FormalDecl{SYMTBL.get("b2"), SYMTBL.getBool()},
                    OptionalExpr{ALLOC_EXPR(ExprArithU( 
                        ALLOC_EXPR(ExprSymbol(SYMTBL.get("Symbol"))), 
                        ExprArithU::OP_NOT))
                    } 
                }
            },
            MethodList{},
            SYMTBL.getObject()
        }
    };
    TestHelper(input, context, expect);
}

TEST(ParserTest, ExprArithBTest) {
    ast::ASTContext context;
    const char* input = 
    R"(
        class Main
        {
            i1 : Int <- 1 + 2;
            i2 : Int <- 1 - 2;
            i3 : Int <- 1 * 2;
            i4 : Int <- 1 / 2;
            i5 : Int <- 1 + 2 * 3;
            i6 : Int <- (1 + 2) * 3;
        };
    )";
    ClassList expect{
        Class{ SYMTBL.get("Main"), 
            AttrList{
                AttrFeature{
                    FormalDecl{SYMTBL.get("i1"), SYMTBL.getInt()},
                    OptionalExpr{ALLOC_EXPR( ExprArithB(
                        ALLOC_EXPR(ExprInt(1)),
                        ALLOC_EXPR(ExprInt(2)),
                        ExprArithB::OP_ADD
                    ))} 
                },
                AttrFeature{
                    FormalDecl{SYMTBL.get("i2"), SYMTBL.getInt()},
                    OptionalExpr{ALLOC_EXPR( ExprArithB(
                        ALLOC_EXPR(ExprInt(1)),
                        ALLOC_EXPR(ExprInt(2)),
                        ExprArithB::OP_SUB
                    ))} 
                },
                AttrFeature{
                    FormalDecl{SYMTBL.get("i3"), SYMTBL.getInt()},
                    OptionalExpr{ALLOC_EXPR( ExprArithB(
                        ALLOC_EXPR(ExprInt(1)),
                        ALLOC_EXPR(ExprInt(2)),
                        ExprArithB::OP_MUL
                    ))} 
                },
                AttrFeature{
                    FormalDecl{SYMTBL.get("i4"), SYMTBL.getInt()},
                    OptionalExpr{ALLOC_EXPR( ExprArithB(
                        ALLOC_EXPR(ExprInt(1)),
                        ALLOC_EXPR(ExprInt(2)),
                        ExprArithB::OP_DIV
                    ))} 
                },
                AttrFeature{
                    FormalDecl{SYMTBL.get("i5"), SYMTBL.getInt()},
                    OptionalExpr{ALLOC_EXPR( ExprArithB(
                        ALLOC_EXPR(ExprInt(1)),
                        ALLOC_EXPR(ExprArithB(
                            ALLOC_EXPR(ExprInt(2)),
                            ALLOC_EXPR(ExprInt(3)),
                            ExprArithB::OP_MUL
                        )),
                        ExprArithB::OP_ADD
                    ))} 
                },
                AttrFeature{
                    FormalDecl{SYMTBL.get("i6"), SYMTBL.getInt()},
                    OptionalExpr{ALLOC_EXPR( ExprArithB(
                        ALLOC_EXPR(ExprArithB(
                            ALLOC_EXPR(ExprInt(1)),
                            ALLOC_EXPR(ExprInt(2)),
                            ExprArithB::OP_ADD
                        )),
                        ALLOC_EXPR(ExprInt(3)),
                        ExprArithB::OP_MUL
                    ))} 
                }
            },
            MethodList{},
            SYMTBL.getObject()
        }
    };
    TestHelper(input, context, expect);
}

TEST(ParserTest, ExprAssignTest) {
    ast::ASTContext context;
    const char* input = 
    R"(
        class Main
        {
            i1 : Int <- Symbol <- 10;
        };
    )";
    ClassList expect{
        Class{ SYMTBL.get("Main"), 
            AttrList{
                AttrFeature{
                    FormalDecl{SYMTBL.get("i1"), SYMTBL.getInt()},
                    OptionalExpr{ALLOC_EXPR(
                        ExprAssign(
                            SYMTBL.get("Symbol"), ALLOC_EXPR(ExprInt(10))
                        )
                    )} 
                }
            },
            MethodList{},
            SYMTBL.getObject()
        }
    };
    TestHelper(input, context, expect);
}

TEST(ParserTest, ExprDispatchTest) {
    ast::ASTContext context;
    const char* input = 
    R"(
        class Main
        {
            i1 : Int <- Obj.call(10, 20.5);
        };
    )";
    ClassList expect{
        Class{ SYMTBL.get("Main"), 
            AttrList{
                AttrFeature{
                    FormalDecl{SYMTBL.get("i1"), SYMTBL.getInt()},
                    OptionalExpr{ ALLOC_EXPR(
                        ExprDispatch(
                            ALLOC_EXPR(ExprSymbol{SYMTBL.get("Obj")}),
                            SYMTBL.get("call"),
                            ExprList{
                                ALLOC_EXPR(ExprInt(10)),
                                ALLOC_EXPR(ExprFloat(20.5))
                            }
                        )
                    )} 
                }
            },
            MethodList{},
            SYMTBL.getObject()
        }
    };
    TestHelper(input, context, expect);
}

TEST(ParserTest, ExprStaticDispatchTest) {
    ast::ASTContext context;
    const char* input = 
    R"(
        class Main
        {
            i1 : Int <- Obj@Type.call(10, 20.5);
        };
    )";
    ClassList expect{
        Class{ SYMTBL.get("Main"), 
            AttrList{
                AttrFeature{
                    FormalDecl{SYMTBL.get("i1"), SYMTBL.getInt()},
                    OptionalExpr{ ALLOC_EXPR(
                        ExprStaticDispatch(
                            ALLOC_EXPR(ExprSymbol{SYMTBL.get("Obj")}),
                            SYMTBL.get("Type"),
                            SYMTBL.get("call"),
                            ExprList{
                                ALLOC_EXPR(ExprInt(10)),
                                ALLOC_EXPR(ExprFloat(20.5))
                            }
                        )
                    )} 
                }
            },
            MethodList{},
            SYMTBL.getObject()
        }
    };
    TestHelper(input, context, expect);
}

TEST(ParserTest, SelfExprDispatchTest) {
    ast::ASTContext context;
    const char* input = 
    R"(
        class Main
        {
            i1 : Int <- call(10, 20.5);
        };
    )";
    ClassList expect{
        Class{ SYMTBL.get("Main"), 
            AttrList{
                AttrFeature{
                    FormalDecl{SYMTBL.get("i1"), SYMTBL.getInt()},
                    OptionalExpr{ ALLOC_EXPR(
                        ExprDispatch(
                            ALLOC_EXPR(ExprSelf()),
                            SYMTBL.get("call"),
                            ExprList{
                                ALLOC_EXPR(ExprInt(10)),
                                ALLOC_EXPR(ExprFloat(20.5))
                            }
                        )
                    )} 
                }
            },
            MethodList{},
            SYMTBL.getObject()
        }
    };
    TestHelper(input, context, expect);
}

TEST(ParserTest, ExprBlockTest) {
    ast::ASTContext context;
    const char* input = 
    R"(
        class Main
        {
            s1 : String <- {10; 20.5; "string";};
        };
    )";
    ClassList expect{
        Class{ SYMTBL.get("Main"), 
            AttrList{
                AttrFeature{
                    FormalDecl{SYMTBL.get("s1"), SYMTBL.getString()},
                    OptionalExpr{ ALLOC_EXPR(
                        ExprBlock(
                            {
                                ALLOC_EXPR(ExprInt(10)),
                                ALLOC_EXPR(ExprFloat(20.5)),
                                ALLOC_EXPR(ExprString("string"))
                            }
                        )
                    )} 
                }
            },
            MethodList{},
            SYMTBL.getObject()
        }
    };
    TestHelper(input, context, expect);
}

TEST(ParserTest, ExprCondTest) {
    ast::ASTContext context;
    const char* input = 
    R"(
        class Main
        {
            i1 : Int <- if b1 then 10 else 20 fi;
        };
    )";
    ClassList expect{
        Class{ SYMTBL.get("Main"), 
            AttrList{
                AttrFeature{
                    FormalDecl{SYMTBL.get("i1"), SYMTBL.getInt()},
                    OptionalExpr{ ALLOC_EXPR(
                        ExprCond(
                            ALLOC_EXPR(ExprSymbol(SYMTBL.get("b1"))),
                            ALLOC_EXPR(ExprInt(10)),
                            ALLOC_EXPR(ExprInt(20))
                        )
                    )} 
                }
            },
            MethodList{},
            SYMTBL.getObject()
        }
    };
    TestHelper(input, context, expect);
}

TEST(ParserTest, ExprLoopTest) {
    ast::ASTContext context;
    const char* input = 
    R"(
        class Main
        {
            i1 : Int <- while not b1 = 0 loop b1 <- b1 - 1 pool;
        };
    )";
    ClassList expect{
        Class{ SYMTBL.get("Main"), 
            AttrList{
                AttrFeature{
                    FormalDecl{SYMTBL.get("i1"), SYMTBL.getInt()},
                    OptionalExpr{ ALLOC_EXPR(
                        ExprLoop(
                            ALLOC_EXPR(
                                ExprArithU(
                                    ALLOC_EXPR(
                                        ExprArithB(
                                            ALLOC_EXPR(ExprSymbol(SYMTBL.get("b1"))), 
                                            ALLOC_EXPR(ExprInt(0)), 
                                            ExprArithB::OP_EQ
                                        )
                                    ), 
                                    ExprArithU::OP_NOT
                                )
                            ),
                            ALLOC_EXPR(
                                ExprAssign(
                                    SYMTBL.get("b1"),
                                    ALLOC_EXPR(
                                        ExprArithB(
                                            ALLOC_EXPR(ExprSymbol(SYMTBL.get("b1"))),
                                            ALLOC_EXPR(ExprInt(1)),
                                            ExprArithB::OP_SUB
                                        )
                                    )
                                )
                            )
                        )
                    )} 
                }
            },
            MethodList{},
            SYMTBL.getObject()
        }
    };
    TestHelper(input, context, expect);
}

TEST(ParserTest, ExprLetTest) {
    ast::ASTContext context;
    const char* input = 
    R"(
        class Main
        {
            i1 : Int <- let s1 : String <- "hello", s2 : String <- "world" in s1;
        };
    )";
    ClassList expect{
        Class{ SYMTBL.get("Main"), 
            AttrList{
                AttrFeature{
                    FormalDecl{SYMTBL.get("i1"), SYMTBL.getInt()},
                    OptionalExpr{ ALLOC_EXPR(
                        ExprLet(
                            LetInitList{
                                LetInit(
                                    FormalDecl(
                                        SYMTBL.get("s1"),
                                        SYMTBL.getString()
                                    ),
                                    ALLOC_EXPR(
                                        ExprString("hello")
                                    )
                                ),
                                LetInit(
                                    FormalDecl(
                                        SYMTBL.get("s2"),
                                        SYMTBL.getString()
                                    ),
                                    ALLOC_EXPR(
                                        ExprString("world")
                                    )
                                )
                            },
                            ALLOC_EXPR(
                                ExprSymbol(
                                    SYMTBL.get("s1")
                                )
                            )
                        )
                    )} 
                }
            },
            MethodList{},
            SYMTBL.getObject()
        }
    };
    TestHelper(input, context, expect);
}


TEST(ParserTest, ExprCaseTest) {
    ast::ASTContext context;
    const char* input = 
    R"(
        class Main
        {
            o1 : Object <- 
                case cond_obj of
                    i : Int => 10;
                    f : Float => 0.5;
                    s : String => "hello";
                esac;
        };
    )";
    ClassList expect{
        Class{ SYMTBL.get("Main"), 
            AttrList{
                AttrFeature{
                    FormalDecl{SYMTBL.get("o1"), SYMTBL.getObject()},
                    OptionalExpr{ ALLOC_EXPR(
                        ExprCase(
                            ALLOC_EXPR(
                                ExprSymbol(SYMTBL.get("cond_obj"))
                            ),
                            CaseBranchList{
                                CaseBranch(
                                    SYMTBL.get("i"),
                                    SYMTBL.getInt(),
                                    ALLOC_EXPR(ExprInt(10))
                                ),
                                CaseBranch(
                                    SYMTBL.get("f"),
                                    SYMTBL.getFloat(),
                                    ALLOC_EXPR(ExprFloat(0.5))
                                ),
                                CaseBranch(
                                    SYMTBL.get("s"),
                                    SYMTBL.getString(),
                                    ALLOC_EXPR(ExprString("hello"))
                                )
                            }
                        )
                    )} 
                }
            },
            MethodList{},
            SYMTBL.getObject()
        }
    };
    TestHelper(input, context, expect);
}

TEST(ParserTest, SelfTest) {
    ast::ASTContext context;
    const char* input = 
    R"(
        class Main
        {
            s : SelfType;
            main() : SelfType {
                s <- new SelfType
            };
            main2() : SelfType {
                self
            };
        };
    )";
    ClassList expect{
        Class{ SYMTBL.get("Main"), 
            AttrList{
                AttrFeature(
                    FormalDecl(SYMTBL.get("s"), SYMTBL.getSelfType()), {}
                )
            },
            MethodList{
                MethodFeature{
                    SYMTBL.get("main"),
                    SYMTBL.getSelfType(),
                    FormalList{},
                    ALLOC_EXPR(ExprAssign(
                        SYMTBL.get("s"),
                        ALLOC_EXPR(
                            ExprNew(SYMTBL.getSelfType())
                        )
                    ))
                },
                MethodFeature{
                    SYMTBL.get("main2"),
                    SYMTBL.getSelfType(),
                    FormalList{},
                    ALLOC_EXPR(ExprSelf())
                }
            },
            SYMTBL.getObject()
        }
    };
    TestHelper(input, context, expect);
}
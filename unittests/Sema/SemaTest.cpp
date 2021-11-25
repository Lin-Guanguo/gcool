#include "gtest/gtest.h"
#include "gcool/Lexer/Lexer.h"
#include "gcool/Parser/Parser.h"
#include "gcool/Sema/Sema.h"
#include <vector>
#include <iostream>

using namespace gcool;
using namespace gcool::sema;
using namespace gcool::ast;

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

    EXPECT_EQ(sema.TheErrorList.size(), errorList.size());
    for(int i = 0; i < errorList.size(); ++i) {
        EXPECT_EQ(sema.TheErrorList[i].TheDiagKind, errorList[i]);
    }
}

TEST(SemaTest, InheritTest) {
    const char* input = 
    R"(
        class Main {};
        class Main {};
        class Main {};
        class Loop1 inherits Loop2 {};
        class Loop2 inherits Loop1 {};
        class ErrorSelf inherits SelfType {};
        class InheritFinal inherits Int {};
    )";
    ErrorKindList errorList = {
        basic::Diag::Sema_RedefineClass,  
        basic::Diag::Sema_RedefineClass,  
        basic::Diag::Sema_InheritFromFinalClass,
        basic::Diag::Sema_LoopInherit,  
        basic::Diag::Sema_LoopInherit,  
        basic::Diag::Sema_LoopInherit,
    };
    checkError(input, errorList, true);
}

TEST(SemaTest, AttrMethodRedefineTest) {
    const char* input = 
    R"(
        class Main {
            i : Int;
            i : Int;
            i : Bool;
            f() : Int {
                10
            };
            f() : Int {
                20
            };
            f() : Int {
                30
            };
        };
    )";
    ErrorKindList errorList = {
        basic::Diag::Sema_AttriMultiDefine,
        basic::Diag::Sema_AttriMultiDefine,
        basic::Diag::Sema_MethodMultiDefine,
        basic::Diag::Sema_MethodMultiDefine,
    };
    checkError(input, errorList, false);
}

TEST(SemaTest, DeclTest) {
    const char* input = 
    R"(
        class Main {
            a : WrongClass;
            b : Int <- true;
            c : Int <- 10;
        };
    )";
    ErrorKindList errorList = {
        basic::Diag::Sema_DeclTypeError,
        basic::Diag::Sema_DeclTypeIncompatible
    };
    checkError(input, errorList, false);
}

TEST(SemaTest, MethodTest) {
    const char* input = 
    R"(
        class Main {
            correct(i : Int) : Int {
                i
            };

            hello() : WrongClass {
                10
            };

            hello2() : Int {
                20.2
            };

            hello3(i : WrongClass) : Int {
                20.2
            };

            hello4() : Int {
                undefineSymbol
            };
        };
    )";
    ErrorKindList errorList = {
        basic::Diag::Sema_MethodRetTypeError,
        basic::Diag::Sema_MethodParamTypeError,
        basic::Diag::Sema_MethodBodyExprTypeIncompatible,
        basic::Diag::Sema_ExprSymbolNotDefine,
        basic::Diag::Sema_MethodBodyExprError
    };
    checkError(input, errorList, false);
}

TEST(SemaTest, SelfTest) {
    const char* input = 
    R"(
        class Main {
            attr1 : SelfType;

            correct1(i : Int) : SelfType {
                self
            };

            correct2(i : Int) : SelfType {
                attr1 <- new SelfType
            };

            correct3() : Main {
                self
            };

            error1() : SelfType {
                attr1 <- new Main
            };

            error2(i : SelfType) : Int {
                10
            };

        };
    )";
    ErrorKindList errorList = {
        basic::Diag::Sema_MethodParamCantBeSelfType,
        basic::Diag::Sema_ExprAssignTypeIncompatible,
        basic::Diag::Sema_MethodBodyExprError
    };
    checkError(input, errorList, false);
}

TEST(SemaTest, SymbolExprTest) {
    const char* input = 
    R"(
        class Main {
            attr1 : SelfType;
            i : Wrong;

            correct1(i : Int) : SelfType {
                attr1
            };

            error1(i : Int) : SelfType {
                at1
            };

            error2(d : Int) : SelfType {
                i
            };

        };
    )";
    ErrorKindList errorList = {
        basic::Diag::Sema_DeclTypeError,
        basic::Diag::Sema_ExprSymbolNotDefine,
        basic::Diag::Sema_MethodBodyExprError,
        basic::Diag::Sema_ExprSymbolTypeError,
        basic::Diag::Sema_MethodBodyExprError
    };
    checkError(input, errorList, false);
}

TEST(SemaTest, AssignExprTest) {
    const char* input = 
    R"(
        class Main {
            attr1 : SelfType;
            int : Int;
            e : Wrong;

            correct1(i : Int) : SelfType {
                attr1 <- self
            };

            error1(i : Int) : Int {
                f <- i
            };

            error2(i : Int) : Int {
                e <- f <- i
            };

            error3(i : Bool) : Int {
                int <- i
            };

        };
    )";
    ErrorKindList errorList = {
        basic::Diag::Sema_DeclTypeError,
        basic::Diag::Sema_ExprAssignVariableNotDecl,
        basic::Diag::Sema_MethodBodyExprError,
        basic::Diag::Sema_ExprAssignVariableTypeError,
        basic::Diag::Sema_ExprAssignVariableNotDecl,
        basic::Diag::Sema_ExprAssignExprError,
        basic::Diag::Sema_MethodBodyExprError,
        basic::Diag::Sema_ExprAssignTypeIncompatible,
        basic::Diag::Sema_MethodBodyExprError
    };
    checkError(input, errorList, false);
}

TEST(SemaTest, DispatchExprTest) {
    const char* input = 
    R"(
        class Main {
            attr1 : SelfType;
            int : Int;

            hello(i : Int) : Int {
                i
            };

            correct1(i : Int) : Int {
                hello(i)
            };

            correct2(i : Int) : Int {
                attr1.correct1(i)
            };

            error1() : Int {
                nodefine.hello()
            };

            error2() : Int {
                world()
            };

            error3() : Int {
                hello(10, 20)
            };

            error4() : Int {
                hello(true)
            };

            error5() : Int {
                hello(nodefine)
            };

        };
    )";
    ErrorKindList errorList = {
        basic::Diag::Sema_ExprSymbolNotDefine,
        basic::Diag::Sema_ExprDispatchCalleeExprError,
        basic::Diag::Sema_MethodBodyExprError,
        basic::Diag::Sema_ExprDispatchMethodUnknow,
        basic::Diag::Sema_MethodBodyExprError,
        basic::Diag::Sema_ExprDispatchArgsNumberError,
        basic::Diag::Sema_MethodBodyExprError,
        basic::Diag::Sema_ExprDispatchArgsTypeError,
        basic::Diag::Sema_MethodBodyExprError,
        basic::Diag::Sema_ExprSymbolNotDefine,
        basic::Diag::Sema_ExprDispatchArgsExprError,
        basic::Diag::Sema_MethodBodyExprError
    };
    checkError(input, errorList, false);
}

TEST(SemaTest, StaticDispatchExprTest) {
    const char* input = 
    R"(
        class Base2 {

        };

        class Base {
            hello() : Int {
                10
            };
        };

        class Main inherits Base {
            attr1 : SelfType;
            int : Int;

            hello() : Int {
                20
            };

            correct1(i : Int) : Int {
                hello()
            };

            correct2(i : Int) : Int {
                self@Base.hello()
            };

            error1(i : Int) : Int {
                self@NoBase.hello()
            };

            error2(i : Int) : Int {
                self@SelfType.hello()
            };

            error3(i : Int) : Int {
                self@Base2.hello()
            };

        };
    )";
    ErrorKindList errorList = {
        basic::Diag::Sema_ExprStaticDispatchTypeUnkonw,
        basic::Diag::Sema_MethodBodyExprError,
        basic::Diag::Sema_ExprStaticDispatchTypeCantBeSelfType,
        basic::Diag::Sema_MethodBodyExprError,
        basic::Diag::Sema_ExprStaticDispatchInheritError,
        basic::Diag::Sema_MethodBodyExprError
    };
    checkError(input, errorList, false);
}



// TODO: Expr error
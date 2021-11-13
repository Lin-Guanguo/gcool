#include "gtest/gtest.h"
#include "gcool/Lexer/Lexer.h"
#include "gcool/Parser/Parser.h"
#include <vector>

TEST(ParserTest, t1)
{
    auto in = R"(
        class  if  then  else  fi
        true  false  while  loop
        pool  in  inherits  let
        case  esac  new  of  not
        isvoid  . @  <-  +  -  *  / =>
        (  )  =  <=  >=  <  >  ;  , { } :
        123  5  9  0  12.5  3.0
        2.5  "string" "str\"str"
        (* a comment
            * just skip
            *) 12
    )";
    std::vector<int> tokens = {
        gcool::Parser::token::TK_CLASS,
        gcool::Parser::token::TK_IF,
        gcool::Parser::token::TK_THEN,
        gcool::Parser::token::TK_ELSE,
        gcool::Parser::token::TK_FI,
        gcool::Parser::token::TK_TRUE,
        gcool::Parser::token::TK_FALSE,
        gcool::Parser::token::TK_WHILE,
        gcool::Parser::token::TK_LOOP,
        gcool::Parser::token::TK_POOL,
        gcool::Parser::token::TK_IN,
        gcool::Parser::token::TK_INHERITS,
        gcool::Parser::token::TK_LET,
        gcool::Parser::token::TK_CASE,
        gcool::Parser::token::TK_ESAC,
        gcool::Parser::token::TK_NEW,
        gcool::Parser::token::TK_OF,
        gcool::Parser::token::TK_NOT,
        gcool::Parser::token::TK_ISVOID,
        gcool::Parser::token::TK_DOT,
        gcool::Parser::token::TK_AT,
        gcool::Parser::token::TK_ASSIGN,
        gcool::Parser::token::TK_ADD,
        gcool::Parser::token::TK_SUB,
        gcool::Parser::token::TK_MUL,
        gcool::Parser::token::TK_DIV,
        gcool::Parser::token::TK_ARROW,
        gcool::Parser::token::TK_LP,
        gcool::Parser::token::TK_RP,
        gcool::Parser::token::TK_EQ,
        gcool::Parser::token::TK_LE,
        gcool::Parser::token::TK_GE,
        gcool::Parser::token::TK_LT,
        gcool::Parser::token::TK_GT,
        gcool::Parser::token::TK_SEMICOLON,
        gcool::Parser::token::TK_COMMA,
        gcool::Parser::token::TK_LB,
        gcool::Parser::token::TK_RB,
        gcool::Parser::token::TK_COLON,
        gcool::Parser::token::TK_INT,
        gcool::Parser::token::TK_INT,
        gcool::Parser::token::TK_INT,
        gcool::Parser::token::TK_INT,
        gcool::Parser::token::TK_FLOAT,
        gcool::Parser::token::TK_FLOAT,
        gcool::Parser::token::TK_FLOAT,
        gcool::Parser::token::TK_STR,
        gcool::Parser::token::TK_STR,
        gcool::Parser::token::TK_INT
    };
    yyscan_t scanner;
    yylex_init(&scanner);
    yy_scan_string(in, scanner);
    gcool::Parser::value_type v;
    for (auto i : tokens) {
        EXPECT_EQ(i, yylex(&v, scanner));
    }
}
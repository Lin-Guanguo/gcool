%option yylineno 
%option reentrant noyywrap noinput nounput batch
%option outfile="Lexer.cpp" header-file="Lexer.h"

%{
#include <cstdlib>
#include <string>
#include "Parser.h"
#define ParserData static_cast<gcool::Parser::value_type*>(yyextra)

%}

%x COMMENT
%x STRING

%%

"(*"                { BEGIN(COMMENT); }
<COMMENT>"*)"       { BEGIN(INITIAL); }
<COMMENT><<EOF>>    { BEGIN(INITIAL); return gcool::Parser::token::TK_ERROR; }
<COMMENT>.          { }

"\""                    { BEGIN(STRING); 
                          ParserData->emplace<std::string>(); }
<STRING>\\[0-9]{1,3}    { unsigned code = atoi(yytext + 1);
                          if (code <= 255) 
                          ParserData->as<std::string>().push_back(static_cast<char>(code)); } //just skip error code
<STRING>"\\a"           { ParserData->as<std::string>().push_back('\a'); }
<STRING>"\\b"           { ParserData->as<std::string>().push_back('\b'); }
<STRING>"\\f"           { ParserData->as<std::string>().push_back('\f'); }
<STRING>"\\n"           { ParserData->as<std::string>().push_back('\n'); }
<STRING>"\\r"           { ParserData->as<std::string>().push_back('\r'); }
<STRING>"\\t"           { ParserData->as<std::string>().push_back('\t'); }
<STRING>"\\v"           { ParserData->as<std::string>().push_back('\v'); }
<STRING>"\\\\"          { ParserData->as<std::string>().push_back('\\'); }
<STRING>"\\\""          { ParserData->as<std::string>().push_back('\"'); }
<STRING>"\\."           { } //just skip non escape char
<STRING>"\""            { BEGIN(INITIAL); return gcool::Parser::token::TK_STR; }
<STRING><<EOF>>         { BEGIN(INITIAL); return gcool::Parser::token::TK_ERROR; }
<STRING>.               { ParserData->as<std::string>().push_back(yytext[0]); }

"class"     { return gcool::Parser::token::TK_CLASS; }
"if"        { return gcool::Parser::token::TK_IF; }
"then"      { return gcool::Parser::token::TK_THEN; }
"else"      { return gcool::Parser::token::TK_ELSE; }
"fi"        { return gcool::Parser::token::TK_FI; }
"true"      { return gcool::Parser::token::TK_TRUE; }
"false"     { return gcool::Parser::token::TK_FALSE; }
"while"     { return gcool::Parser::token::TK_WHILE; }
"loop"      { return gcool::Parser::token::TK_LOOP; }
"pool"      { return gcool::Parser::token::TK_POOL; }
"in"        { return gcool::Parser::token::TK_IN; }
"inherits"  { return gcool::Parser::token::TK_INHERITS; }
"let"       { return gcool::Parser::token::TK_LET; }
"case"      { return gcool::Parser::token::TK_CASE; }
"esac"      { return gcool::Parser::token::TK_ESAC; }
"new"       { return gcool::Parser::token::TK_NEW; }
"of"        { return gcool::Parser::token::TK_OF; }
"self"      { return gcool::Parser::token::TK_SELF; }

"not"       { return gcool::Parser::token::TK_NOT; }
"isvoid"    { return gcool::Parser::token::TK_ISVOID; }
"."         { return gcool::Parser::token::TK_DOT; }
"@"         { return gcool::Parser::token::TK_AT; }
"<-"        { return gcool::Parser::token::TK_ASSIGN; }
"=>"        { return gcool::Parser::token::TK_ARROW; }
"+"         { return gcool::Parser::token::TK_ADD; }
"-"         { return gcool::Parser::token::TK_SUB; }
"*"         { return gcool::Parser::token::TK_MUL; }
"/"         { return gcool::Parser::token::TK_DIV; }
"("         { return gcool::Parser::token::TK_LP; }
")"         { return gcool::Parser::token::TK_RP; }
"{"         { return gcool::Parser::token::TK_LB; }
"}"         { return gcool::Parser::token::TK_RB; }
"="         { return gcool::Parser::token::TK_EQ; }
"<="        { return gcool::Parser::token::TK_LE; }
">="        { return gcool::Parser::token::TK_GE; }
"<"         { return gcool::Parser::token::TK_LT; }
">"         { return gcool::Parser::token::TK_GT; }
";"         { return gcool::Parser::token::TK_SEMICOLON; }
":"         { return gcool::Parser::token::TK_COLON; }
","         { return gcool::Parser::token::TK_COMMA; }

[0-9]+                  { ParserData->emplace<int>(std::atoi(yytext)); return gcool::Parser::token::TK_INT; }
[0-9]+"."[0-9]+         { ParserData->emplace<double>(std::atof(yytext)); return gcool::Parser::token::TK_FLOAT; }
[a-zA-Z_][a-zA-Z0-9_]*  { ParserData->emplace<const char*>(yytext); return gcool::Parser::token::TK_SYMBOL; }

[ \r\t\n]+    { }

.             { return gcool::Parser::token::TK_ERROR; }


%%

// Parser's yylex call, warp to Lexer's yylex
int yylex(gcool::Parser::value_type* parserData, yyscan_t scannner) { 
    yyset_extra(static_cast<void*>(parserData), scannner);
    return yylex(scannner);
}
%require "3.8"
%language "c++"
%header "Parser.h"
%output "Parser.cpp"
%define api.namespace {gcool}
%define api.parser.class {Parser}
%define api.token.prefix {TK_}
%define api.value.type variant


%code requires{
    #include <string>
    typedef void* yyscan_t;
}
%code provides{
    int yylex(gcool::Parser::value_type* parserData, yyscan_t scannner);
}
%parse-param    {yyscan_t scannner}
%lex-param      {yyscan_t scannner}


%{

%}

%token CLASS IF THEN ELSE FI TRUE FALSE WHILE LOOP POOL IN INHERITS ISVOID LET CASE ESAC NEW OF NOT
%token DOT AT ASSIGN ARROW ADD SUB MUL DIV LP RP LB RB EQ LE GE LT GT SEMICOLON COMMA COLON
%token<const char*> SYMBOL ERROR
%token<std::string> STR
%token<int> INT
%token<double> FLOAT


// Conflict resolution
%nonassoc NOT ISVOID
%right ASSIGN
%precedence IN
%left LE LT GE GT EQ
%left ADD SUB
%left MUL DIV
%left DOT AT

%%

program: class_seq
    ;

class_seq: class SEMICOLON
    | class_seq class SEMICOLON
    ;

class: CLASS symbol inherits LB features RB
    ;

inherits:
    | INHERITS symbol
    ;

symbol: SYMBOL
    ;

formal: symbol COLON symbol
    ;

features:
    | features formal optional_assign SEMICOLON
    | features symbol LP params RP COLON symbol LB expr RB SEMICOLON
    ;

optional_assign:
    | ASSIGN expr
    ;

expr: symbol
    | TRUE
    | FALSE
    | INT
    | FLOAT
    | STR
    | symbol ASSIGN expr
    | expr DOT symbol LP args RP
    | expr AT symbol DOT symbol LP args RP
    | symbol LP args RP
    | IF expr THEN expr ELSE expr FI
    | WHILE expr LOOP expr POOL
    | LB block_exprs RB
    | LET let_init_exprs IN expr
    | CASE expr OF case_branchs ESAC
    | NEW symbol
    | ISVOID expr
    | NOT expr
    | expr ADD expr
    | expr SUB expr
    | expr MUL expr
    | expr DIV expr
    | expr EQ expr
    | expr LE expr
    | expr LT expr
    | expr GE expr
    | expr GT expr
    | LP expr RP
    ;

params:
    | params_
    ;

params_: formal
    | params_ COMMA formal
    ;

args:
    | args_
    ;

args_: expr
    | args_ COMMA expr
    ;

block_exprs: expr SEMICOLON
    | block_exprs expr SEMICOLON
    ;

let_init_exprs: formal optional_assign
    | let_init_exprs COMMA formal optional_assign
    ;

case_branchs: formal ARROW expr SEMICOLON
    | case_branchs formal ARROW expr SEMICOLON
    ;



%%

void gcool::Parser::error(const std::string& s) {
    printf("error: %s", s.data());
}

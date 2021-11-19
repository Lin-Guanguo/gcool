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
    #include <optional>
    #include "gcool/AST/AST.h"
    #include "gcool/AST/Expr.h"
    typedef void* yyscan_t;

    template<typename T>
    class NoneInitHolder : public std::optional<T>{
    public:
        using std::optional<T>::optional;
        using std::optional<T>::operator =;
        operator T() {
            return this->value();
        }
    };
}
%code provides{
    int yylex(gcool::Parser::value_type* parserData, yyscan_t scannner);
}
%parse-param    {yyscan_t scannner} {gcool::ast::ASTContext* context}
%lex-param      {yyscan_t scannner}


%{
    #include "gcool/AST/AST.h"
    #include "gcool/AST/Expr.h"
    using namespace gcool::ast;
%}

%token CLASS IF THEN ELSE FI TRUE FALSE WHILE LOOP POOL IN INHERITS ISVOID LET CASE ESAC NEW OF NOT
%token DOT AT ASSIGN ARROW ADD SUB MUL DIV LP RP LB RB EQ LE GE LT GT SEMICOLON COMMA COLON SELF
%token<const char*> SYMBOL ERROR
%token<std::string> STR
%token<int> INT
%token<double> FLOAT

// Type Without default Constructor should wrap with NoneInitHolder
%type<NoneInitHolder<gcool::ast::Symbol>> symbol inherits
%type<NoneInitHolder<gcool::ast::FormalDecl>> formal
%type<NoneInitHolder<gcool::ast::Expr>> expr
%type<NoneInitHolder<gcool::ast::Class>> class features
%type<gcool::ast::OptionalExpr> optional_assign
%type<gcool::ast::ClassList> class_seq
%type<gcool::ast::FormalList> params params_
%type<gcool::ast::ExprList> args args_ block_exprs
%type<gcool::ast::LetInitList> let_init_exprs
%type<gcool::ast::CaseBranchList> case_branchs

// Conflict resolution
%nonassoc NOT ISVOID
%right ASSIGN
%precedence IN
%left LE LT GE GT EQ
%left ADD SUB
%left MUL DIV
%left DOT AT

%%

program: class_seq                  { context->Classes = std::move($1); }
    ;

class_seq:                          { $$ = ClassList{}; }
    | class_seq class SEMICOLON     { $$ = std::move($1); $$.push_back(std::move($2)); }
    ;

class: CLASS symbol inherits LB features RB { $$ = std::move($5); $$->Inheirt = $3; $$->Name = $2; }
    ;

inherits:               { $$ = context->Symtbl.getObject(); }
    | INHERITS symbol   { $$ = $2; }
    ;

symbol: SYMBOL  { $$ = context->Symtbl.get($1); }
    ;

formal: symbol COLON symbol { $$ = FormalDecl{$1, $3}; }
    ;

features:   { $$ = Class{ Symbol::EmptySymbol, Symbol::EmptySymbol }; }
    | features formal optional_assign SEMICOLON  { $$ = std::move($1); $$->Attrs.push_back(AttrFeature{$2, $3}); }
    | features symbol LP params RP COLON symbol LB expr RB SEMICOLON    { $$ = std::move($1); $$->Methods.push_back(MethodFeature{$2, $7, std::move($4), $9}); }
    ;

optional_assign:   { $$ = OptionalExpr{}; }
    | ASSIGN expr  { $$ = $2; }
    ;

params:         { $$ = FormalList{}; }
    | params_   { $$ = std::move($1); }
    ;

params_: formal             { $$ = FormalList{}; $$.push_back($1); }
    | params_ COMMA formal  { $$ = std::move($1); $$.push_back($3); }
    ;

expr: symbol    { $$ = context->ExprAlloc.allocExpr(ExprSymbol($1)); }
    | TRUE      { $$ = context->ExprAlloc.allocExpr(ExprBool(true)); }
    | FALSE     { $$ = context->ExprAlloc.allocExpr(ExprBool(false)); }
    | INT       { $$ = context->ExprAlloc.allocExpr(ExprInt($1)); }
    | FLOAT     { $$ = context->ExprAlloc.allocExpr(ExprFloat($1)); }
    | STR       { $$ = context->ExprAlloc.allocExpr(ExprString($1)); }
    | symbol ASSIGN expr            { $$ = context->ExprAlloc.allocExpr(ExprAssign($1, $3)); }
    | expr DOT symbol LP args RP    { $$ = context->ExprAlloc.allocExpr(ExprDispatch($1, $3, std::move($5))); }
    | expr AT symbol DOT symbol LP args RP  { $$ = context->ExprAlloc.allocExpr(ExprStaticDispatch($1, $3, $5, std::move($7))); }
    | symbol LP args RP                     { $$ = context->ExprAlloc.allocExpr(ExprDispatch(context->ExprAlloc.allocExpr(ExprSelf()), $1, std::move($3))); }
    | IF expr THEN expr ELSE expr FI        { $$ = context->ExprAlloc.allocExpr(ExprCond($2, $4, std::move($6))); }
    | WHILE expr LOOP expr POOL         { $$ = context->ExprAlloc.allocExpr(ExprLoop($2, $4)); }
    | LB block_exprs RB                 { $$ = context->ExprAlloc.allocExpr(ExprBlock(std::move($2))); }
    | LET let_init_exprs IN expr        { $$ = context->ExprAlloc.allocExpr(ExprLet(std::move($2), $4)); }
    | CASE expr OF case_branchs ESAC    { $$ = context->ExprAlloc.allocExpr(ExprCase($2, std::move($4))); }
    | NEW symbol    { $$ = context->ExprAlloc.allocExpr(ExprNew($2)); }
    | ISVOID expr   { $$ = context->ExprAlloc.allocExpr(ExprArithU($2, ExprArithU::OP_ISVOID)); }
    | NOT expr      { $$ = context->ExprAlloc.allocExpr(ExprArithU($2, ExprArithU::OP_NOT)); }
    | expr ADD expr { $$ = context->ExprAlloc.allocExpr(ExprArithB($1, $3, ExprArithB::OP_ADD)); }
    | expr SUB expr { $$ = context->ExprAlloc.allocExpr(ExprArithB($1, $3, ExprArithB::OP_SUB)); }
    | expr MUL expr { $$ = context->ExprAlloc.allocExpr(ExprArithB($1, $3, ExprArithB::OP_MUL)); }
    | expr DIV expr { $$ = context->ExprAlloc.allocExpr(ExprArithB($1, $3, ExprArithB::OP_DIV)); }
    | expr EQ expr  { $$ = context->ExprAlloc.allocExpr(ExprArithB($1, $3, ExprArithB::OP_EQ)); }
    | expr LE expr  { $$ = context->ExprAlloc.allocExpr(ExprArithB($1, $3, ExprArithB::OP_LE)); }
    | expr LT expr  { $$ = context->ExprAlloc.allocExpr(ExprArithB($1, $3, ExprArithB::OP_LT)); }
    | expr GE expr  { $$ = context->ExprAlloc.allocExpr(ExprArithB($1, $3, ExprArithB::OP_GE)); }
    | expr GT expr  { $$ = context->ExprAlloc.allocExpr(ExprArithB($1, $3, ExprArithB::OP_GT)); }
    | LP expr RP    { $$ = $2; }
    | SELF          { $$ = context->ExprAlloc.allocExpr(ExprSelf()); }
    ;

args:           { $$ = ExprList{}; }
    | args_     { $$ = std::move($1); }
    ;

args_: expr             { $$ = ExprList{}; $$.push_back($1); }
    | args_ COMMA expr  { $$ = std::move($1); $$.push_back($3); }
    ;

block_exprs: expr SEMICOLON         { $$ = ExprList{}; $$.push_back($1); }
    | block_exprs expr SEMICOLON    { $$ = std::move($1); $$.push_back($2); }
    ;

let_init_exprs: formal optional_assign             { $$ = LetInitList{}; $$.push_back({$1, $2}); }
    | let_init_exprs COMMA formal optional_assign  { $$ = std::move($1); $$.push_back({$3, $4}); }
    ;

case_branchs: symbol COLON symbol ARROW expr SEMICOLON          { $$ = CaseBranchList{}; $$.push_back({$1, $3, $5}); }
    | case_branchs symbol COLON symbol ARROW expr SEMICOLON     { $$ = std::move($1); $$.push_back({$2, $4, $6}); }
    ;



%%

void gcool::Parser::error(const std::string& s) {
    printf("error: %s", s.data());
}

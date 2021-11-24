#pragma once
#include <string>
#include <string_view>
#include "gcool/AST/Symbol.h"
#include "gcool/AST/ExprFwd.h"
#include "gcool/AST/AST.h"

namespace gcool {
namespace ast {

struct LetInit {
    FormalDecl Formal;
    OptionalExpr Init;
public:
    LetInit(FormalDecl formal, OptionalExpr initVal)
        : Formal(formal), Init(initVal) {}
    bool operator==(const LetInit&) const = default;
};

struct CaseBranch {
    FormalDecl Formal;
    Expr Body;
    CaseBranch(FormalDecl formal, Expr body)
        : Formal(formal), Body(body) {}
public:
    bool operator==(const CaseBranch&) const = default;
};

using CaseBranchList = std::vector<CaseBranch>;
using LetInitList = std::vector<LetInit>;

class ExprBase {
public:
    enum ExprKind {
        #define EXPR_KIND_DEF(EK, CLASS) EK,
        #include "gcool/AST/ExprKindDef.def"
    };
private:
    ExprKind __TheKind;
protected:
    ExprBase(ExprKind kind) : __TheKind(kind) {}
public:
    ExprKind getKind() const { return __TheKind; }
    bool operator==(const ExprBase& that) const;
};

template<typename T>
class ExprFacility : public ExprBase {
protected:
    ExprFacility() : ExprBase(T::TheKind) {}
public:
    static bool classof(const ExprBase* D) {
        return D->getKind() == T::TheKind;
    }
    bool operator==(const ExprFacility& t) const { 
        return getKind() == t.getKind(); 
    };
};

class ExprInt : public ExprFacility<ExprInt> {
public:
    static constexpr ExprKind TheKind = EK_INT;
    int Val;
public:
    ExprInt(int i) : Val(i) {}
    bool operator==(const ExprInt&) const = default;
};

class ExprFloat : public ExprFacility<ExprFloat> {
public:
    static constexpr ExprKind TheKind = EK_FLOAT;
    double Val;
public:
    ExprFloat(double f) : Val(f) {}
    bool operator==(const ExprFloat&) const = default;
};

class ExprBool : public ExprFacility<ExprBool> {
public:
    static constexpr ExprKind TheKind = EK_BOOL;
    bool Val;
public:
    ExprBool(bool b) : Val(b) {}
    bool operator==(const ExprBool&) const = default;
};

class ExprString : public ExprFacility<ExprString> {
public:
    static constexpr ExprKind TheKind = EK_STRING;
    std::string Val;
public:
    ExprString(std::string_view s) : Val(s) {}
    bool operator==(const ExprString&) const = default;
};

class ExprSymbol : public ExprFacility<ExprSymbol> {
public:
    static constexpr ExprKind TheKind = EK_SYMBOL;
    Symbol TheSymbol;
public:
    ExprSymbol(Symbol s) : TheSymbol(s) {}
    bool operator==(const ExprSymbol&) const = default;
};

class ExprAssign : public ExprFacility<ExprAssign> {
public:
    static constexpr ExprKind TheKind = EK_ASSIGN;
    Symbol Variable;
    Expr Value;
public:
    ExprAssign(Symbol variable, Expr value) : Variable(variable), Value(value) {}
    bool operator==(const ExprAssign&) const = default;
};

class ExprDispatch : public ExprFacility<ExprDispatch> {
public:
    static constexpr ExprKind TheKind = EK_DISPATCH;
    Expr Callee;
    Symbol Method;
    ExprList Args;
public:
    ExprDispatch(Expr callee, Symbol method, ExprList&& args) 
        : Callee(callee), Method(method), Args(std::move(args)) {}
    bool operator==(const ExprDispatch&) const = default;
};

class ExprStaticDispatch : public ExprFacility<ExprStaticDispatch> {
public:
    static constexpr ExprKind TheKind = EK_STATIC_DISPATCH;
    Expr Callee;
    Symbol Type;
    Symbol Method;
    ExprList Args;
public:
    ExprStaticDispatch(Expr callee, Symbol type, Symbol method, ExprList&& args) 
        : Callee(callee), Type(type), Method(method), Args(std::move(args)) {}
    bool operator==(const ExprStaticDispatch&) const = default;
};

class ExprCond : public ExprFacility<ExprCond> {
public:
    static constexpr ExprKind TheKind = EK_COND;
    Expr Cond;
    Expr ThenBranch;
    Expr ElseBranch;
public:
    ExprCond(Expr cond, Expr thenBranch, Expr elseBranch)
        : Cond(cond), ThenBranch(thenBranch), ElseBranch(elseBranch) {}
    bool operator==(const ExprCond&) const = default;
};

class ExprLoop : public ExprFacility<ExprLoop> {
public:
    static constexpr ExprKind TheKind = EK_LOOP;
    Expr Cond;
    Expr LoopBody;
public:
    ExprLoop(Expr cond, Expr loopBody)
        : Cond(cond), LoopBody(loopBody) {}
    bool operator==(const ExprLoop&) const = default;
};

class ExprCase : public ExprFacility<ExprCase> {
public:
    static constexpr ExprKind TheKind = EK_CASE;
    Expr Cond;
    CaseBranchList Branchs;
public:
    ExprCase(Expr cond, CaseBranchList&& branchs)
        : Cond(cond), Branchs(std::move(branchs)) {}
    bool operator==(const ExprCase&) const = default;
};

class ExprBlock : public ExprFacility<ExprBlock> {
public:
    static constexpr ExprKind TheKind = EK_BLOCK;
    ExprList Exprs;
public:
    ExprBlock(ExprList&& exprs)
        : Exprs(std::move(exprs)) {}
    bool operator==(const ExprBlock&) const = default;
};

class ExprLet : public ExprFacility<ExprLet> {
public:
    static constexpr ExprKind TheKind = EK_LET;
    LetInitList InitVariables;
    Expr LetBody;
public:
    ExprLet(LetInitList&& initVariables, Expr letBody)
        : InitVariables(initVariables), LetBody(letBody) {}
    bool operator==(const ExprLet&) const = default;
};

class ExprNew : public ExprFacility<ExprNew> {
public:
    static constexpr ExprKind TheKind = EK_NEW;
    Symbol Type;
public:
    ExprNew(Symbol type) : Type(type) {}
    bool operator==(const ExprNew&) const = default;
};

class ExprSelf : public ExprFacility<ExprSelf> {
public:
    static constexpr ExprKind TheKind = EK_SELF;
public:
    ExprSelf() {}
    bool operator==(const ExprSelf&) const = default;
};

class ExprArithB : public ExprFacility<ExprArithB> {
public:
    static constexpr ExprKind TheKind = EK_ARITH_B;
    static constexpr const char* OperatorLiteral[] = {
        #define BINARY_OPERATOR_DEF(OperatorKind, String, OverloadFunction) String,
        #include "gcool/AST/OperatorDef.def"
    };
    static constexpr const char* OverloadFuncName[] = {
        #define BINARY_OPERATOR_DEF(OperatorKind, String, OverloadFunction) OverloadFunction,
        #include "gcool/AST/OperatorDef.def"
    };
    enum Op : int {
        #define BINARY_OPERATOR_DEF(OperatorKind, String, OverloadFunction) OperatorKind,
        #include "gcool/AST/OperatorDef.def"
    };
    Expr Left;
    Expr Right;
    Op Operator;
public:
    ExprArithB(Expr left, Expr right, Op op)
        : Left(left), Right(right), Operator(op) {}
    bool operator==(const ExprArithB&) const = default;
};

class ExprArithU : public ExprFacility<ExprArithU> {
public:
    static constexpr ExprKind TheKind = EK_ARITH_U;
    static constexpr const char* OperatorLiteral[] = {
        #define UNARY_OPERATOR_DEF(OperatorKind, String, OverloadFunction) String,
        #include "gcool/AST/OperatorDef.def"
    };
    static constexpr const char* OverloadFuncName[] = {
        #define UNARY_OPERATOR_DEF(OperatorKind, String, OverloadFunction) OverloadFunction,
        #include "gcool/AST/OperatorDef.def"
    };
    enum Op : int {
        #define UNARY_OPERATOR_DEF(OperatorKind, String, OverloadFunction) OperatorKind,
        #include "gcool/AST/OperatorDef.def"
    };
    Expr Operand;
    Op Operator;
public:
    ExprArithU(Expr operand, Op op)
        : Operand(operand), Operator(op) {}
    bool operator==(const ExprArithU&) const = default;
};

}
}
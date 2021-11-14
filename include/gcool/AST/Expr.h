#pragma once
#include <optional>
#include <string>
#include <string_view>
#include "llvm/Support/Casting.h"
#include "gcool/AST/Symbol.h"
#include "gcool/AST/ExprFwd.h"

namespace gcool{
namespace ast{

struct CaseBranch;
struct LetInit;
using OptionalExpr = std::optional<Expr>;
using CaseBranchList = std::vector<CaseBranch>;
using LetInitList = std::vector<LetInit>;
using ExprList = std::vector<Expr>;

class ExprAllocator {
private:
    ExprList FreeList;
public:
    ExprAllocator() {}
    Expr allocExpr(ExprBase* e);
    ~ExprAllocator();
};

class ExprBase {
public:
    enum ExprKind {
        #define EXPR_KIND_DEF(EK, CLASS) EK,
        #include "gcool/AST/ExprKindDef.def"
    };
private:
    ExprKind __TheKind;
protected:
    ExprBase(ExprKind kind) : __TheKind(kind) { }
public:
    ExprKind getKind() const { return __TheKind; }
    bool operator==(const ExprBase& that) const;
};

template<typename T>
class ExprFacility : public ExprBase {
protected:
    ExprFacility() : ExprBase(T::TheKind) { }
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
    ExprInt(int i) : Val(i) { }
    bool operator==(const ExprInt&) const = default;
};

class ExprFloat : public ExprFacility<ExprFloat> {
public:
    static constexpr ExprKind TheKind = EK_FLOAT;
    double Val;
public:
    ExprFloat(double f) : Val(f) { }
    bool operator==(const ExprFloat&) const = default;
};

class ExprBool : public ExprFacility<ExprBool> {
public:
    static constexpr ExprKind TheKind = EK_BOOL;
    bool Val;
public:
    ExprBool(bool b) : Val(b) { }
    bool operator==(const ExprBool&) const = default;
};

class ExprString : public ExprFacility<ExprString> {
public:
    static constexpr ExprKind TheKind = EK_STRING;
    std::string Val;
public:
    ExprString(std::string_view s) : Val(s) { }
    bool operator==(const ExprString&) const = default;
};

class ExprSymbol : public ExprFacility<ExprSymbol> {
public:
    static constexpr ExprKind TheKind = EK_SYMBOL;
    Symbol TheSymbol;
public:
    bool operator==(const ExprSymbol&) const = default;
};

class ExprAssign : public ExprFacility<ExprAssign> {
public:
    static constexpr ExprKind TheKind = EK_ASSIGN;
    Symbol Variable;
    Expr Value;
public:
    bool operator==(const ExprAssign&) const = default;
};

class ExprDispatch : public ExprFacility<ExprDispatch> {
public:
    static constexpr ExprKind TheKind = EK_DISPATCH;
    Expr Callee;
    Symbol Method;
    ExprList Args;
public:
    bool operator==(const ExprDispatch&) const = default;
};

class ExprStaticDispatch : public ExprFacility<ExprStaticDispatch> {
public:
    static constexpr ExprKind TheKind = EK_STATIC_DISPATCH;
    Expr Callee;
    Expr Type;
    Symbol Method;
    ExprList Args;
public:
    bool operator==(const ExprStaticDispatch&) const = default;
};

class ExprCond : public ExprFacility<ExprCond> {
public:
    static constexpr ExprKind TheKind = EK_COND;
    Expr Cond;
    Expr ThenBranch;
    Expr ElseBranch;
public:
    bool operator==(const ExprCond&) const = default;
};

class ExprLoop : public ExprFacility<ExprLoop> {
public:
    static constexpr ExprKind TheKind = EK_LOOP;
    Expr Cond;
    Expr LoopBody;
public:
    bool operator==(const ExprLoop&) const = default;
};

struct CaseBranch {
    Symbol Name;
    Symbol Type;
    Expr e;
    bool operator==(const CaseBranch&) const = default;
};

class ExprCase : public ExprFacility<ExprCase> {
public:
    static constexpr ExprKind TheKind = EK_CASE;
    Expr Cond;
    CaseBranchList Branchs;
public:
    bool operator==(const ExprCase&) const = default;
};

class ExprBlock : public ExprFacility<ExprBlock> {
public:
    static constexpr ExprKind TheKind = EK_BLOCK;
    ExprList Exprs;
public:
    bool operator==(const ExprBlock&) const = default;
};

struct LetInit {
    Symbol Name;
    Symbol Type;
    OptionalExpr InitVal;
    bool operator==(const LetInit&) const = default;
};

class ExprLet : public ExprFacility<ExprLet> {
public:
    static constexpr ExprKind TheKind = EK_LET;
    LetInitList InitVariables;
    Expr LetBody;
public:
    bool operator==(const ExprLet&) const = default;
};

class ExprNew : public ExprFacility<ExprNew> {
public:
    static constexpr ExprKind TheKind = EK_NEW;
    Symbol Type;
public:
    bool operator==(const ExprNew&) const = default;
};

class ExprSelf : public ExprFacility<ExprSelf> {
public:
    static constexpr ExprKind TheKind = EK_SELF;
public:
    bool operator==(const ExprSelf&) const = default;
};

class ExprArithB : public ExprFacility<ExprArithB> {
public:
    static constexpr ExprKind TheKind = EK_ARITH_B;
    enum Op {
        OP_ADD,
        OP_SUB,
        OP_MUL,
        OP_DIV,
    };
    Expr Left;
    Expr Right;
    Op Operator;
public:
    bool operator==(const ExprArithB&) const = default;
};

class ExprArithU : public ExprFacility<ExprArithU> {
public:
    static constexpr ExprKind TheKind = EK_ARITH_U;
    enum Op {
        OP_NOT,
        OP_ISVOID,
    };
    Expr Val;
    Op Operator;
public:
    bool operator==(const ExprArithU&) const = default;
};

}
}
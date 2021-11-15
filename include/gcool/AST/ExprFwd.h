#pragma once
#include <optional>
#include <vector>

namespace gcool{
namespace ast{

#define EXPR_KIND_DEF(EK, CLASS) class CLASS;
#include "gcool/AST/ExprKindDef.def"

class ExprBase;
class Expr;
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

class Expr {
private:
    ExprBase* TheExpr;
    Expr(ExprBase* e) : TheExpr(e) {}
    friend class ExprAllocator;
public:
    Expr(const Expr& e) = default;
    Expr(Expr&& e) = default;
    Expr& operator=(Expr e) { TheExpr = e.TheExpr; return *this; }
    
    bool operator==(Expr t) const;
    ExprBase& operator*();
    ExprBase* operator->();
};


}
}
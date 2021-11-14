#pragma once

namespace gcool{
namespace ast{

#define EXPR_KIND_DEF(EK, CLASS) class CLASS;
#include "gcool/AST/ExprKindDef.def"

class ExprBase;
class ExprAllocator;
class Expr {
private:
    ExprBase* TheExpr;
    Expr(ExprBase* e) : TheExpr(e) {}
    friend class ExprAllocator;
public:
    Expr(const Expr& e) = default;
    Expr(Expr&& e) = default;
    
    bool operator==(Expr t) const;
    ExprBase& operator*();
    ExprBase* operator->();
};


}
}
#pragma once
#include <optional>
#include <vector>

namespace gcool {
namespace sema {
    class ExprAnnotation;
}

namespace ast {

#define EXPR_KIND_DEF(EK, CLASS) class CLASS;
#include "gcool/AST/ExprKindDef.def"

class ExprBase;
class Expr;
class ExprAllocator;
class ExprVisitor;
using OptionalExpr = std::optional<Expr>;
using ExprList = std::vector<Expr>;
using ExprBaseList = std::vector<ExprBase*>;


class Expr {
private:
    ExprBase* TheExpr;
    Expr(ExprBase* e) : TheExpr(e) {}
    friend class ExprAllocator;
public:
    sema::ExprAnnotation* Annotation = nullptr;
public:
    Expr(const Expr& e) = default;
    Expr(Expr&& e) = default;
    Expr& operator=(Expr e) { TheExpr = e.TheExpr; return *this; }
    
    bool operator==(Expr t) const;
    ExprBase& operator*();
    ExprBase* operator->();
    void replace(Expr e) { TheExpr = e.TheExpr; }
    void accept(ExprVisitor& visitor);
};

class ExprAllocator {
private:
    ExprBaseList FreeList;
public:
    ExprAllocator() {}
    template<typename T>
    Expr allocExpr(T&& e) {
        auto p = new T(std::forward<T>(e));
        FreeList.push_back(p);
        return Expr(p);
    }
    ~ExprAllocator();
};

class ExprVisitor {
public:
    #define EXPR_KIND_DEF(EK, CLASS) \
        virtual void operator()(Expr& expr, CLASS& rawExpr) = 0;
    #include "gcool/AST/ExprKindDef.def"
};


}
}
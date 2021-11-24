#include <cassert>
#include "llvm/Support/Casting.h"
#include "gcool/AST/Expr.h"

bool gcool::ast::Expr::operator==(Expr t) const { 
    return *this->TheExpr == *t.TheExpr; 
}

gcool::ast::ExprBase& gcool::ast::Expr::operator*() { 
    return *TheExpr; 
}

gcool::ast::ExprBase* gcool::ast::Expr::operator->() { 
    return TheExpr; 
}

void gcool::ast::Expr::accept(ExprVisitor& visitor) {
    switch (TheExpr->getKind()) {
        #define EXPR_KIND_DEF(EK, CLASS)    \
            case gcool::ast::ExprBase::EK:  \
                visitor(*this, llvm::cast<CLASS>(*(this->TheExpr))); break;
        #include "gcool/AST/ExprKindDef.def"
        default:
            assert(0 && "never reached case");
    }
}

gcool::ast::ExprAllocator::~ExprAllocator() {
    for(auto i : this->FreeList){
        delete i;
    }
}

bool gcool::ast::ExprBase::operator==(const ExprBase& that) const{
    if (this->getKind() != that.getKind())
        return false;
    switch (this->getKind()) {
        #define EXPR_KIND_DEF(EK, CLASS) \
            case EK: return llvm::cast<CLASS>(*this) == llvm::cast<CLASS>(that);
        #include "gcool/AST/ExprKindDef.def"
        default:
            assert(0 && "never reached case");
    }
};


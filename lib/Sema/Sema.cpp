#include "gcool/Sema/Sema.h"
#include "gcool/AST/Expr.h"
#include <unordered_set>
#include <stack>

using namespace gcool;
using namespace gcool::ast;
using namespace gcool::sema;

const gcool::sema::SemaScoop gcool::sema::SemaScoop::EmptyScoop = nullptr;

gcool::sema::ExprAnnotation* gcool::sema::Sema::allocExprAnnotation(ast::Symbol type) {
    auto p = new ExprAnnotation(type);
    this->AnnotationFreeList.push_back(p);
    return p;
}

gcool::sema::Sema::~Sema() {
    for(auto p : this->AnnotationFreeList) 
        delete p;
}

bool gcool::sema::Sema::checkAll() {
    bool checkResult = true;
    if (!inheritCheck())
        return false;
    if (!exprCheck())
        checkResult = false;
    return checkResult;
}

bool gcool::sema::Sema::inheritCheck() {
    bool checkResult = true;
    std::unordered_set<ast::Symbol> className;
    for(auto& c : TheASTContext->Classes) {
        if (className.find(c.Name) != className.end()) {
            checkResult = false;
            TheErrorList.push_back(
                {basic::Diag::Sema_RedefineClass, std::string(c.Name.getName())});
        }
        else
            className.insert(c.Name);
    }
    std::stack<ast::Symbol> parent;
    parent.push(TheASTContext->Symtbl.getObject());
    while (!parent.empty()) {
        auto p = parent.top(); 
        parent.pop();
        for (auto& c : TheASTContext->Classes) {
            if (c.Inheirt == p) {
                parent.push(c.Name);
                className.erase(c.Name);
            }
        }
    }
    if (!className.empty()) {
        checkResult = false;
        for (auto c : className)
            TheErrorList.push_back(
                {basic::Diag::Sema_LoopInherit, std::string(c.getName())});
    }
    return checkResult;
}

namespace {

#define SYMTBL TheSema.TheASTContext->Symtbl

class SemaExprVisitor : public gcool::ast::ExprVisitor {
public:
    gcool::sema::Sema& TheSema;
    const gcool::sema::SemaScoop* TheScoop;
    SemaExprVisitor(gcool::sema::Sema& theSema, const SemaScoop* outerScoop)
        : TheSema(theSema), TheScoop(outerScoop) {}
    
public:
    void operator()(Expr& expr, ExprInt& rawExpr) {
        expr.Annotation = TheSema.allocExprAnnotation(SYMTBL.getInt());
    }
    void operator()(Expr& expr, ExprFloat& rawExpr) {
        expr.Annotation = TheSema.allocExprAnnotation(SYMTBL.getFloat());
    }
    void operator()(Expr& expr, ExprBool& rawExpr) {
        expr.Annotation = TheSema.allocExprAnnotation(SYMTBL.getBool());
    }
    void operator()(Expr& expr, ExprString& rawExpr) {
        expr.Annotation = TheSema.allocExprAnnotation(SYMTBL.getString());
    }
    void operator()(Expr& expr, ExprSymbol& rawExpr) {
        auto type = TheScoop->searchVariable(rawExpr.TheSymbol);
        auto annot = TheSema.allocExprAnnotation(type);
        if (type.isEmpty())
            annot->hasError = true;
        expr.Annotation = annot;
    }
    void operator()(Expr& expr, ExprAssign& rawExpr) {
        rawExpr.Value.accept(*this);
        auto variableType = TheScoop->searchVariable(rawExpr.Variable);
        auto annot = TheSema.allocExprAnnotation(variableType);
        if (variableType.isEmpty() 
            || rawExpr.Value.Annotation->Type != variableType)
            annot->hasError = true;
        expr.Annotation = annot;
    }
    void operator()(Expr& expr, ExprDispatch& rawExpr) {
        
    }
    void operator()(Expr& expr, ExprStaticDispatch& rawExpr) {

    }
    void operator()(Expr& expr, ExprCond& rawExpr) {

    }
    void operator()(Expr& expr, ExprLoop& rawExpr) {

    }
    void operator()(Expr& expr, ExprCase& rawExpr) {

    }
    void operator()(Expr& expr, ExprBlock& rawExpr) {

    }
    void operator()(Expr& expr, ExprLet& rawExpr) {

    }
    void operator()(Expr& expr, ExprNew& rawExpr) {

    }
    void operator()(Expr& expr, ExprSelf& rawExpr) {

    }
    void operator()(Expr& expr, ExprArithB& rawExpr) {

    }
    void operator()(Expr& expr, ExprArithU& rawExpr) {

    }
};

}

bool gcool::sema::Sema::exprCheck() {
    SemaExprVisitor s(*this, &SemaScoop::EmptyScoop);
    return true;
}


ast::Symbol gcool::sema::SemaScoop::searchVariable(ast::Symbol name) const {
    auto p = this;
    while (p != nullptr) {
        auto vp = p->Variables.find(name);
        if (vp != p->Variables.end())
            return vp->second;
    }
    return ast::Symbol::EmptySymbol;
}

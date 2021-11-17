#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include "gcool/AST/AST.h"
#include "gcool/Basic/Diag.h"

namespace gcool {
namespace sema {

class ExprAnnotation;
class Sema;
class SemaScoop;
using ErrorList = std::vector<basic::Diag>;
using AnnotationList = std::vector<ExprAnnotation*>;
using ScoopVariable = std::unordered_map<ast::Symbol, ast::Symbol>; // Name -> Type

class ASTAnnotation {

};

class ClassAnnotation {

};

class MethodAnnotation {

};

class ExprAnnotation {
public:
    bool hasError = false;
    ast::Symbol Type;
private:
    ExprAnnotation(ast::Symbol type) : Type(type) {}
    friend class Sema;
};

class Sema {
public:
    ErrorList TheErrorList;
    ast::ASTContext* TheASTContext;
    AnnotationList AnnotationFreeList;
public:
    Sema(ast::ASTContext* theASTContext) 
        : TheASTContext(theASTContext) {};
    ~Sema();
    ExprAnnotation* allocExprAnnotation(ast::Symbol type);
    bool checkAll();
    bool inheritCheck();
    bool exprCheck();

};

class SemaScoop {
public:
    const SemaScoop* OuterScoop;
    ScoopVariable Variables;
public:
    SemaScoop(SemaScoop* outer) : OuterScoop(outer) {}
    ast::Symbol searchVariable(ast::Symbol name) const;

    static const SemaScoop EmptyScoop;
};

}
}
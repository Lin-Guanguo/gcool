#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include "gcool/AST/AST.h"
#include "gcool/Basic/Diag.h"
#include "gcool/Sema/Annotation.h"

namespace gcool {
namespace sema {

class Annotation;
class Sema;
using ErrorList = std::vector<basic::Diag>;
using AnnotationList = std::vector<Annotation*>;

class Sema {
public:
    ErrorList TheErrorList;
    AnnotationList AnnotationFreeList;
    ast::ASTContext* TheASTContext;
public:
    Sema(ast::ASTContext* theASTContext) 
        : TheASTContext(theASTContext) {};
    ~Sema();

    template<typename T, typename... Args>
    T* allocAnnotation(Args&&... args) {
        auto p = new T(std::forward(args)...);
        this->AnnotationFreeList.push_back(p);
        return p;
    }

    // return hasError
    bool checkAll();

    // add builtinType
    bool pass0();

    // alloc Annotation for AST, Class, Method, Attr
    // build Class Index Map
    // build Method Index Map, check multi defination
    // build Attr Scope, check multi defination
    bool pass1();

    // check class multi defination
    // check class inherits, add Annotion Class* to super, InheritDepth
    // if error, not continue check
    bool pass2();

    // check Attr Type, Attr Expr
    // check Method RetType, Args Type, Body Expr 
    // build Method Scope
    bool pass3();

    // pass3 help function
    bool checkDecl(ast::FormalDecl& formal, ast::OptionalExpr& init, sema::SemaScope* Scope, ast::Class* selfClass);
    bool checkMethod(ast::MethodFeature& method, sema::SemaScope* Scope, ast::Class* selfClass);
    bool checkExpr(ast::Expr& e, sema::SemaScope* Scope, ast::Class* selfClass);

    // return two type is Inherits or the same;
    // only after pass2
    bool isSuper(ast::Class* super, ast::Class* sub, ast::Class* selfClass);

    // return two type's common super;
    // only after pass2
    ast::Class* getCommonSuper(ast::Class* sub1, ast::Class* sub2, ast::Class* selfClass);

    void addError(basic::Diag&& error);
};

}
}
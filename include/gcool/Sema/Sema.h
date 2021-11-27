#pragma once
#include <vector>
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
    bool pass1();

    // alloc Annotation for AST, Class, Method, Attr
    // build Class Index Map
    // build Method Index Map, check multi defination
    bool pass2();

    // check class multi defination
    // check class inherits, add Annotion Class* to super, InheritDepth
    // set error class annotation to error
    bool pass3();

    // annotAttrDecl annotMethodDecl
    // add AttrOffset and MethodOffset
    bool pass4();

    // check expr
    bool pass5();

    // pass3 help function
    void annotClassKind(ast::Class* c);
    bool annotAttrDecl(ast::Class* Class);
    bool annotMethodDecl(ast::Class* Class);
    bool checkExpr(ast::Expr& e, sema::SemaScope* Scope, ast::Class* selfClass);

    // return two type is Inherits or the same;
    // only after pass2
    bool isSuper(ast::Class* super, ast::Class* sub, ast::Class* selfClass);

    // return two type's common super;
    // only after pass2
    ast::Class* getCommonSuper(ast::Class* sub1, ast::Class* sub2, ast::Class* selfClass);


    void addBuiltinTypeAST();

    void addError(basic::Diag&& error);
};

}
}
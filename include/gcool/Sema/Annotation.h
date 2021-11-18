#pragma once
#include <unordered_map>
#include "gcool/AST/AST.h"

namespace gcool {
namespace sema {

using ScopeVariable = std::unordered_map<ast::Symbol, ast::FormalDecl*>;
using ClassListMap = std::unordered_map<ast::Symbol, ast::Class*>;
using MethodListMap = std::unordered_map<ast::Symbol, ast::MethodFeature*>;

class SemaScope {
public:
    SemaScope* OuterScope;
    ast::Class* InClass;
    ScopeVariable Variables;
public:
    SemaScope() 
        : OuterScope (nullptr), InClass(nullptr) {}
    SemaScope(SemaScope* outer) 
        : OuterScope(outer), InClass(outer->InClass) {}

    struct VariableDecl {
        SemaScope* Scope;
        ast::FormalDecl* Decl;
    };
    VariableDecl searchVariable(ast::Symbol name);
    void addVariable(ast::FormalDecl& formal);

    static SemaScope EmptyScope;
};

class Annotation {
public:
    bool hasError = false;
protected:
    Annotation() {};
};

class ASTAnnotation : public Annotation {
public:
    ClassListMap ClassMap;
protected:
    ASTAnnotation() {}
    friend class Sema;
public:
    ast::Class* findClass(ast::Symbol Name);
};

class ClassAnnotation : public Annotation {
public:
    MethodListMap MethodMap;
    SemaScope Scope;
    ast::Class* SuperClass;
    int InheritDepth;
protected:
    ClassAnnotation() : Scope() {}
    friend class Sema;
public:
    ast::MethodFeature* findMethod(ast::Symbol Name);
    ast::FormalDecl* findAttr(ast::Symbol Name);
};

class AttrAnnotation : public Annotation {
public:

protected:
    AttrAnnotation() {}
    friend class Sema;
};

class MethodAnnotation : public Annotation {
public:
    SemaScope MethodScope;
    ast::Class* RetClass = nullptr;
protected:
    MethodAnnotation() {}
    friend class Sema;
};

class ExprAnnotation : public Annotation {
public:
    ast::Class* Type = nullptr;
protected:
    ExprAnnotation() {}
    friend class Sema;
};

class ExprSymbolAnnotation : public ExprAnnotation {
public:
    SemaScope* ScopeRef = nullptr;
    ast::FormalDecl* DeclRef = nullptr;
protected:
    ExprSymbolAnnotation() {}
    friend class Sema;
};

// TODO
class ExprDidpatchAnnotation : public ExprAnnotation {
public:
    ast::Class* ClassRef = nullptr;
    ast::MethodFeature* MethodRef = nullptr;
protected:
    ExprDidpatchAnnotation() {}
    friend class Sema;
};



}
}
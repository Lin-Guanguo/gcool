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
    ScopeVariable Variables;
public:
    SemaScope() 
        : OuterScope (nullptr) {}
    SemaScope(SemaScope* outer) 
        : OuterScope(outer) {}

    struct VariableDecl {
        SemaScope* Scope;
        ast::FormalDecl* Decl;
    };
    VariableDecl searchVariable(ast::Symbol name);
    void addVariable(ast::FormalDecl& formal);

    static SemaScope EmptyScope;
};

class MethodTable {
public:
    MethodTable* SuperClassTable;
    ast::Class* InClass;
    MethodListMap ClassMethod;
public:
    struct MethodDecl {
        ast::Class* InClass;
        ast::MethodFeature* Decl;
    };
    MethodTable()
        : SuperClassTable(nullptr), InClass(nullptr) {}

    MethodTable(ast::Class* curClass)
        : SuperClassTable(nullptr), InClass(curClass) {}

    MethodTable(MethodTable* super, ast::Class* curClass)
        : SuperClassTable(super), InClass(curClass) {}

    MethodDecl findMethod(ast::Symbol Name);
    MethodDecl findMethodInClass(ast::Symbol Name);
    void addMethod(ast::MethodFeature& method);
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
    MethodTable MTable;
    SemaScope Scope;
    ast::Class* SuperClass;
    int InheritDepth;
protected:
    ClassAnnotation() : Scope() {}
    friend class Sema;
public:

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
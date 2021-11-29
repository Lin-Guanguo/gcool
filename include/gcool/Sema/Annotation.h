#pragma once
#include <unordered_map>
#include <tuple>
#include <vector>
#include "gcool/AST/AST.h"

namespace gcool {
namespace sema {

class SemaScope;
using ScopeVariable = std::unordered_map<ast::Symbol, std::tuple<ast::FormalDecl*, int>>; // name -> FormalDecl, localOffset
using ClassListMap = std::unordered_map<ast::Symbol, ast::Class*>;
using MethodListMap = std::unordered_map<ast::Symbol, ast::MethodFeature*>;
using ClassRefList = std::vector<ast::Class*>;
using ScopeList = std::vector<SemaScope>;

class SemaScope {
public:
    enum ScopeKind {
        SK_Class,
        SK_Method,
        SK_Local
    };
private:
    ScopeVariable Variables;
    SemaScope* OuterScope;
    ScopeKind TheScopeKind;
    int Depth;
    int LocalVarN = 0;
public:
    SemaScope(ScopeKind scopeKind) 
        : OuterScope (nullptr), TheScopeKind(scopeKind), Depth(0) {}
    SemaScope(SemaScope* outer, ScopeKind scopeKind) 
        : TheScopeKind(scopeKind) { setOuter(outer); }

    void setOuter(SemaScope* outer);
    ScopeKind getKind() const { return TheScopeKind; }
    int getDepth() const { return Depth; }
    int getLocalVarN() const { return LocalVarN; }
    auto begin() { return Variables.begin(); }
    auto end() { return Variables.end(); }
    struct VariableDecl {
        SemaScope* Scope;
        ast::FormalDecl* Decl;
        int Offset;
    };
    VariableDecl findVariable(ast::Symbol name);
    void addVariable(ast::FormalDecl& formal, int AttrOffset = -1);

};


class MethodTable {
public:
    MethodTable* SuperClassTable;
    ast::Class* InClass;
private:
    MethodListMap ClassMethod;
public:
    MethodTable()
        : SuperClassTable(nullptr), InClass(nullptr) {}

    MethodTable(ast::Class* curClass)
        : SuperClassTable(nullptr), InClass(curClass) {}

    MethodTable(MethodTable* super, ast::Class* curClass)
        : SuperClassTable(super), InClass(curClass) {}

    struct MethodDecl {
        ast::Class* InClass;
        ast::MethodFeature* Decl;
    };
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
    ClassRefList InheritOrder;
protected:
    ASTAnnotation() {}
    friend class Sema;
public:
    ast::Class* findClass(ast::Symbol Name);
};

class ClassAnnotation : public Annotation {
public:
    MethodTable MTable;
    SemaScope Scope = SemaScope::SK_Class;
    ast::Class* SuperClass;
    int InheritDepth;
    int AttrOffsetEnd;
    int MethodOffsetEnd; 
    int InitLocalVarN = 0; // 初始化时需要的局部变量个数

    enum ClassKind {
        CK_Trivial,
        CK_Object,
        CK_Primitive,
        CK_Abstract,
    };

    ClassKind TheClassKind = CK_Trivial;
protected:
    ClassAnnotation() {}
    friend class Sema;
public:

};

class AttrAnnotation : public Annotation {
public:
    int AttrOffset;
    ast::Class* DeclType = nullptr;
protected:
    AttrAnnotation() {}
    friend class Sema;
};

class MethodAnnotation : public Annotation {
public:
    SemaScope MethodScope = SemaScope::SK_Method;
    ast::Class* InClass = nullptr;
    int MethodOffset;
    int BodyLocalVarN = 0;
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

class ExprIntAnnotation : public ExprAnnotation {
public:
protected:
    ExprIntAnnotation() {}
    friend class Sema;
};

class ExprFloatAnnotation : public ExprAnnotation {
public:
protected:
    ExprFloatAnnotation() {}
    friend class Sema;
};

class ExprBoolAnnotation : public ExprAnnotation {
public:
protected:
    ExprBoolAnnotation() {}
    friend class Sema;
};

class ExprStringAnnotation : public ExprAnnotation {
public:
protected:
    ExprStringAnnotation() {}
    friend class Sema;
};

class ExprSymbolAnnotation : public ExprAnnotation {
public:
    SemaScope* ScopeRef = nullptr;
protected:
    ExprSymbolAnnotation() {}
    friend class Sema;
};

class ExprAssignAnnotation : public ExprAnnotation {
public:
    SemaScope* ScopeRef = nullptr;
protected:
    ExprAssignAnnotation() {}
    friend class Sema;
};

class ExprDispatchAnnotation : public ExprAnnotation {
public:
    ast::Class* StaticMethodClassRef = nullptr;
    ast::MethodFeature* StaticMethodRef = nullptr;
protected:
    ExprDispatchAnnotation() {}
    friend class Sema;
};

class ExprStaticDispatchAnnotation : public ExprDispatchAnnotation {
protected:
    ExprStaticDispatchAnnotation() {}
    friend class Sema;
};

class ExprCondAnnotation : public ExprAnnotation {
public:
protected:
    ExprCondAnnotation() {}
    friend class Sema;
};

class ExprLoopAnnotation : public ExprAnnotation {
public:
protected:
    ExprLoopAnnotation() {}
    friend class Sema;
};

class ExprCaseAnnotation : public ExprAnnotation {
public:
    ScopeList BranchScope;
protected:
    ExprCaseAnnotation() {}
    friend class Sema;
};

class ExprBlockAnnotation : public ExprAnnotation {
public:
protected:
    ExprBlockAnnotation() {}
    friend class Sema;
};

class ExprLetAnnotation : public ExprAnnotation {
public:
    SemaScope LocalScope = SemaScope::SK_Local;
protected:
    ExprLetAnnotation() {}
    friend class Sema;
};

class ExprNewAnnotation : public ExprAnnotation {
public:
    bool IsSelfType = false;
protected:
    ExprNewAnnotation() {}
    friend class Sema;
};

class ExprSelfAnnotation : public ExprAnnotation {
public:
protected:
    ExprSelfAnnotation() {}
    friend class Sema;
};

class ExprNullAnnotation : public ExprAnnotation {
public:
protected:
    ExprNullAnnotation() {}
    friend class Sema;
};

class ExprArithBAnnotation : public ExprAnnotation {
public:
    ast::Class* StaticMethodClassRef = nullptr;
    ast::MethodFeature* StaticMethodRef = nullptr;
protected:
    ExprArithBAnnotation() {}
    friend class Sema;
};

class ExprArithUAnnotation : public ExprAnnotation {
public:
    ast::Class* StaticMethodClassRef = nullptr;
    ast::MethodFeature* StaticMethodRef = nullptr;
protected:
    ExprArithUAnnotation() {}
    friend class Sema;
};



}
}
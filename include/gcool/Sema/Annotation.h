#pragma once
#include <unordered_map>
#include <vector>
#include "gcool/AST/AST.h"

namespace gcool {
namespace sema {

class SemaScope;
using ScopeVariable = std::unordered_map<ast::Symbol, ast::FormalDecl*>;
using ClassListMap = std::unordered_map<ast::Symbol, ast::Class*>;
using MethodListMap = std::unordered_map<ast::Symbol, ast::MethodFeature*>;
using ScopeList = std::vector<SemaScope>;

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
    int AttrOffsetEnd;
    int MethodOffsetEnd; 
protected:
    ClassAnnotation() : Scope() {}
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
    SemaScope MethodScope;
    ast::Class* RetClass = nullptr;
    int MethodOffset;
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
    ast::FormalDecl* DeclRef = nullptr;
protected:
    ExprSymbolAnnotation() {}
    friend class Sema;
};

class ExprAssignAnnotation : public ExprAnnotation {
public:
protected:
    ExprAssignAnnotation() {}
    friend class Sema;
};

class ExprDispatchAnnotation : public ExprAnnotation {
public:
    ast::Class* ClassRef = nullptr;
    ast::MethodFeature* MethodRef = nullptr;
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
    SemaScope LocalScope;
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

class ExprArithBAnnotation : public ExprAnnotation {
public:
    enum ArithBKind : int {
        AK_Error,
        AK_MethodOver,

        AK_IntADD,
        AK_IntSUB,
        AK_IntMUL,
        AK_IntDIV,
        AK_IntEQ,
        AK_IntGE,
        AK_IntGT,
        AK_IntLE,
        AK_IntLT,
        AK_FloatADD,
        AK_FloatSUB,
        AK_FloatMUL,
        AK_FloatDIV,
        AK_FloatEQ,
        AK_FloatGE,
        AK_FloatGT,
        AK_FloatLE,
        AK_FloatLT,
        AK_BoolADD_OR,
        AK_BoolMUL_AND
    };
    // for method Over type
    ArithBKind ArithKind = AK_Error;
    ast::Class* ClassRef = nullptr;
    ast::MethodFeature* MethodRef = nullptr;
protected:
    ExprArithBAnnotation() {}
    friend class Sema;
public:
    ArithBKind ArithBKindSet(ast::Class* left, ast::Class* right, int op);
};

class ExprArithUAnnotation : public ExprAnnotation {
public:
    enum ArithUKind : int {
        AK_Error,
        AK_MethodOver,

        AK_BoolNOT,
        AK_ObjectISVOID
    };
    ArithUKind ArithKind = AK_Error;
    ast::Class* ClassRef = nullptr;
    ast::MethodFeature* MethodRef = nullptr;
protected:
    ExprArithUAnnotation() {}
    friend class Sema;
public:
    ArithUKind ArithUKindSet(ast::Class* operand, int op);
};



}
}
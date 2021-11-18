#pragma once
#include "gcool/AST/Symbol.h"
#include "gcool/AST/ExprFwd.h"
#include <vector>

namespace gcool {
namespace sema {
    class ASTAnnotation;
    class ClassAnnotation;
    class AttrAnnotation;
    class MethodAnnotation;
}

namespace ast {

class FormalDecl;
class AttrFeature;
class MethodFeature;
class Class;

using ClassList = std::vector<Class>;
using AttrList = std::vector<AttrFeature>;
using MethodList = std::vector<MethodFeature>;
using FormalList = std::vector<FormalDecl>;


class FormalDecl {
public:
    Symbol Name;
    Symbol Type;
public:
    FormalDecl(Symbol name, Symbol type)
        : Name(name), Type(type) {}
    bool operator==(const FormalDecl&) const = default;
};

class MethodFeature {
public:
    Symbol Name;
    Symbol RetType;
    FormalList FormalParams;
    Expr Body;
    sema::MethodAnnotation* Annotation = nullptr;
public:
    MethodFeature(Symbol name, Symbol retType, FormalList&& params, Expr body)
        : Name(name), RetType(retType), FormalParams(params), Body(body) {}
    bool operator==(const MethodFeature&) const = default;
};

class AttrFeature {
public:
    FormalDecl Formal;
    OptionalExpr Init;
    sema::AttrAnnotation* Annotation = nullptr;
public:
    AttrFeature(FormalDecl formal, OptionalExpr init)
        : Formal(formal), Init(init) {}
    bool operator==(const AttrFeature&) const = default;
};

class Class {
public:
    Symbol Name;
    AttrList Attrs;
    MethodList Methods;
    Symbol Inheirt;
    sema::ClassAnnotation* Annotation = nullptr;
public:
    Class(Symbol name, Symbol inheirt) : Name(name), Inheirt(inheirt) {}
    Class(Symbol name, AttrList&& attrs, MethodList&& methods, Symbol inheirt) 
        : Name(name), Attrs(attrs), Methods(methods), Inheirt(inheirt) {}
    bool operator==(const Class&) const = default;
};

class ASTContext {
public:
    ClassList Classes;
    SymbolTable Symtbl;
    ExprAllocator ExprAlloc;
    sema::ASTAnnotation* Annotation = nullptr;
public:
    ASTContext();

};

    
}
}
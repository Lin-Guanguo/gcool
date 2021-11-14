#pragma once
#include "gcool/AST/Symbol.h"
#include "gcool/AST/Expr.h"
#include <vector>

namespace gcool {
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

};

class MethodFeature {
public:
    Symbol Name;
    Symbol RetType;
    FormalList FormalParams;
public:

};

class AttrFeature {
public:
    FormalDecl Formal;
    OptionalExpr Init;
public:

};

class Class {
public:
    AttrList Attrs;
    MethodList Methods;
public:

};

class ASTContext {
public:
    ClassList Classes;
    SymbolTable Symtbl;
    ExprAllocator ExprAlloc;
public:

};

    
}
}
#include "gcool/Sema/Annotation.h"

using namespace gcool;

gcool::sema::SemaScope gcool::sema::SemaScope::EmptyScope{};

gcool::sema::SemaScope::VariableDecl gcool::sema::SemaScope::searchVariable(ast::Symbol name) {
    auto p = this;
    while (p != nullptr) {
        auto vp = p->Variables.find(name);
        if (vp != p->Variables.end())
            return {p, vp->second};
        p = p->OuterScope;
    }
    return {nullptr, nullptr};
}

void gcool::sema::SemaScope::addVariable(ast::FormalDecl& formal) {
    this->Variables.insert({formal.Name, &formal});
}

gcool::sema::MethodTable::MethodDecl gcool::sema::MethodTable::findMethod(ast::Symbol Name) {
    auto p = this;
    while (p != nullptr) {
        auto m = p->ClassMethod.find(Name);
        if (m != p->ClassMethod.end())
            return {p->InClass, m->second};
        p = p->SuperClassTable;
    }
    return {nullptr, nullptr};
}

gcool::sema::MethodTable::MethodDecl gcool::sema::MethodTable::findMethodInClass(ast::Symbol Name) {
    auto m = ClassMethod.find(Name);
    if (m != ClassMethod.end())
        return {InClass, m->second};
    return {nullptr, nullptr};
}

void gcool::sema::MethodTable::addMethod(ast::MethodFeature& method) {
    this->ClassMethod.insert({method.Name, &method});
}


ast::Class* gcool::sema::ASTAnnotation::findClass(ast::Symbol Name) {
    auto p = this->ClassMap.find(Name);
    if (p == this->ClassMap.end())
        return nullptr;
    else
        return p->second;
}

sema::ExprArithBAnnotation::ArithBKind sema::ExprArithBAnnotation::ArithBKindSet(
    ast::Class* left, ast::Class* right, int op) {
    // TODO
    return AK_Error;
}

sema::ExprArithUAnnotation::ArithUKind sema::ExprArithUAnnotation::ArithUKindSet(
    ast::Class* operand, int op) {
    // TODO
    return AK_Error;
}


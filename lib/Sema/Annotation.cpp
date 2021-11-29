#include "gcool/Sema/Annotation.h"

using namespace gcool;

void gcool::sema::SemaScope::setOuter(SemaScope* outer) {
    OuterScope = outer;
    Depth = outer->Depth + 1;
}

gcool::sema::SemaScope::VariableDecl gcool::sema::SemaScope::findVariable(ast::Symbol name) {
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

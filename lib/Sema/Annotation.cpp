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


ast::Class* gcool::sema::ASTAnnotation::findClass(ast::Symbol Name) {
    auto p = this->ClassMap.find(Name);
    if (p == this->ClassMap.end())
        return nullptr;
    else
        return p->second;
}

ast::MethodFeature* gcool::sema::ClassAnnotation::findMethod(ast::Symbol Name) {
    auto p = this->MethodMap.find(Name);
    if (p == this->MethodMap.end())
        return nullptr;
    else
        return p->second;
}

ast::FormalDecl* gcool::sema::ClassAnnotation::findAttr(ast::Symbol Name) {
    auto p = Scope.searchVariable(Name);
    return p.Decl;
}


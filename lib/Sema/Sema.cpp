#include "gcool/Sema/Sema.h"
#include "gcool/AST/Expr.h"
#include <unordered_set>
#include <stack>

using namespace gcool;
using namespace gcool::ast;
using namespace gcool::sema;

gcool::sema::Sema::~Sema() {
    for(auto p : this->AnnotationFreeList) 
        delete p;
}

bool gcool::sema::Sema::checkAll() {
    bool hasError = false;
    if (pass0())
        hasError = true;
    if (pass1())
        hasError = true;
    if (pass2()) // if error return
        return true;
    if (pass3())
        hasError = true;
    return hasError;
}

bool gcool::sema::Sema::pass0() {
    TheASTContext->Classes.push_back( 
        Class{TheASTContext->Symtbl.getObject(), Symbol::EmptySymbol} );
    TheASTContext->Classes.push_back( 
        Class{TheASTContext->Symtbl.getInt(), TheASTContext->Symtbl.getObject()} );
    TheASTContext->Classes.push_back( 
        Class{TheASTContext->Symtbl.getFloat(), TheASTContext->Symtbl.getObject()} );
    TheASTContext->Classes.push_back( 
        Class{TheASTContext->Symtbl.getBool(), TheASTContext->Symtbl.getObject()} );
    TheASTContext->Classes.push_back( 
        Class{TheASTContext->Symtbl.getString(), TheASTContext->Symtbl.getObject()} );
    TheASTContext->Classes.push_back( 
        Class{TheASTContext->Symtbl.getSelfType(), Symbol::EmptySymbol} );
    for (auto& a : TheASTContext->Classes) {
        a.Attrs.push_back(AttrFeature{
            FormalDecl{TheASTContext->Symtbl.getSelf(), a.Name}, {}
        });
    }
    return false;
}

// TODO: 继承关系影响 Scoop和MethodMap
bool gcool::sema::Sema::pass1() {
    bool hasError = false;
    std::unordered_set<ast::Symbol> nameSet;
    // check for name multi defination, return hasError
    auto multiDefineCheck = [&nameSet](ast::Symbol s) -> bool {
        if (nameSet.find(s) == nameSet.end()) {
            nameSet.insert(s);
            return false;
        } else 
            return true;
    };
    // construct Name Index Table
    // ClassName -> Class*
    // MethodName -> MethodFeature*
    // AttrName -> FormalDecl*
    TheASTContext->Annotation = allocAnnotation<ASTAnnotation>();
    for (auto& c : TheASTContext->Classes) {
        TheASTContext->Annotation->ClassMap.insert( {c.Name, &c} );
        c.Annotation = allocAnnotation<ClassAnnotation>();
        nameSet.clear();
        for (auto& a : c.Attrs) {
            if (multiDefineCheck(a.Formal.Name)) {
                hasError = true;
                addError({basic::Diag::Sema_AttriMultiDefine, std::string(a.Formal.Name.getName())});
            }
            c.Annotation->Scope.addVariable(a.Formal);
            a.Annotation = allocAnnotation<AttrAnnotation>();
        }
        nameSet.clear();
        for (auto& m : c.Methods) {
            if (multiDefineCheck(m.Name)) {
                hasError = true;
                addError({basic::Diag::Sema_MethodMultiDefine, std::string(m.Name.getName())});
            }
            c.Annotation->MTable.addMethod(m);
            c.Annotation->MTable.InClass = &c;
            m.Annotation = allocAnnotation<MethodAnnotation>();
        }
    }
    TheASTContext->Annotation->hasError = TheASTContext->Annotation->hasError || hasError;
    return hasError;
}

bool gcool::sema::Sema::pass2() {
    bool hasError = false;
    std::unordered_set<ast::Symbol> classNameSet;
    for(auto& c : TheASTContext->Classes) {
        if (classNameSet.find(c.Name) != classNameSet.end()) {
            hasError = true;
            addError({basic::Diag::Sema_RedefineClass, std::string(c.Name.getName())});
        } else {
            classNameSet.insert(c.Name);
        }
    }

    auto root = TheASTContext->Annotation->findClass(
        TheASTContext->Symtbl.getObject()
    );
    root->Annotation->SuperClass = nullptr;
    root->Annotation->InheritDepth = 0;
    classNameSet.erase(root->Name);
    classNameSet.erase(TheASTContext->Symtbl.getSelfType()); // Inherit from SelfType is forbid
    std::stack<Class*> parent;
    parent.push(root);
    while (!parent.empty()) {
        auto super = parent.top(); 
        parent.pop();
        for (auto& c : TheASTContext->Classes) {
            if (c.Inheirt == super->Name) {
                c.Annotation->SuperClass = super;
                c.Annotation->InheritDepth = super->Annotation->InheritDepth + 1;
                c.Annotation->MTable.SuperClassTable = &super->Annotation->MTable;
                parent.push(&c);
                classNameSet.erase(c.Name);
            }
        }
    }
    if (!classNameSet.empty()) {
        hasError = true;
        for (auto c : classNameSet) {
            addError({basic::Diag::Sema_LoopInherit, std::string(c.getName())});
        }
    }
    return hasError;
}

bool gcool::sema::Sema::pass3() {
    bool hasError = false;
    // check for all Expr
    for (auto& c : TheASTContext->Classes) {
        bool classHasError = false;
        for (auto& a : c.Attrs) {
            bool attrHasError = checkDecl(a.Formal, a.Init, &sema::SemaScope::EmptyScope, &c);
            a.Annotation->hasError = attrHasError;
            classHasError = attrHasError || classHasError;
        }
        for (auto& m : c.Methods) {
            bool methodHasError = checkMethod(m, &c.Annotation->Scope, &c);
            m.Annotation->hasError = methodHasError || m.Annotation->hasError;
            classHasError =  methodHasError || classHasError;
        }
        c.Annotation->hasError = classHasError;
        hasError = classHasError || hasError;
    }
    return hasError;
}

bool gcool::sema::Sema::checkDecl(ast::FormalDecl& formal, ast::OptionalExpr& init, sema::SemaScope* scope, ast::Class* selfClass) {
    bool hasError = false;

    // check decl type
    // can be SelfType
    auto c1 = TheASTContext->Annotation->findClass(formal.Type);
    if (!c1) {
        hasError = true;
        addError({basic::Diag::Sema_DeclTypeNotFound, 
            std::string(formal.Type.getName())});
    }

    // check init epxr
    if (init.has_value()) {
        // check epxr
        if (checkExpr(init.value(), scope, selfClass)) {
            hasError = true;
            addError({basic::Diag::Sema_DeclInitExprError, 
                std::string(formal.Name.getName()) + " : " + formal.Type.getName().data()});
        } else {
            auto c2 = init->Annotation->Type;
            // check assign is compatible
            if (!isSuper(c1, c2, selfClass)) {
                hasError = true;
                addError({basic::Diag::Sema_DeclInitTypeIncompatible, 
                    std::string(c1->Name.getName()) + "<-" + 
                    std::string(c2->Name.getName())
                    });
            }
        }
    }
    return hasError;
}

bool gcool::sema::Sema::checkMethod(ast::MethodFeature& method, sema::SemaScope* scope, ast::Class* selfClass) {
    bool hasError = false;

    // check return type
    method.Annotation->RetClass = TheASTContext->Annotation->findClass(method.RetType);
    if (!method.Annotation->RetClass) {
        hasError = true;
        addError({basic::Diag::Sema_MethodUndefinedRetType, std::string(method.RetType.getName())});
    }

    // check params
    method.Annotation->MethodScope = SemaScope(scope);
    for (auto& f : method.FormalParams) {
        if (!TheASTContext->Annotation->findClass(f.Type)) {
            hasError = true;
            addError({basic::Diag::Sema_MethodUndefinedParamType, std::string(f.Type.getName())});
        } else if (f.Type == TheASTContext->Symtbl.getSelfType()) {
            hasError = true;
            addError({basic::Diag::Sema_MethodParamCantBeSelfType, ""});
        }
        
        method.Annotation->MethodScope.addVariable(f);
    }
    
    // check body expr
    if (checkExpr(method.Body, &method.Annotation->MethodScope, selfClass)) {
        hasError = true;
        addError({basic::Diag::Sema_MethodBodyExprError, std::string(method.Name.getName())});
    } 
    
    // check assign expr to return type is compatible
    if (!hasError 
        && !isSuper(method.Annotation->RetClass, method.Body.Annotation->Type, selfClass)) {
        hasError = true;
        addError({basic::Diag::Sema_MethodRetTypeIncompatible, 
            std::string(method.RetType.getName()) + "<-" +
            std::string(method.Body.Annotation->Type->Name.getName())
            });
    }
    
    method.Annotation->hasError = hasError;
    return hasError;
}


namespace {

#define SYMTBL TheSema.TheASTContext->Symtbl
#define GETCLASS(Sym) TheSema.TheASTContext->Annotation->findClass(Sym)

class SemaExprVisitor : public gcool::ast::ExprVisitor {
public:
    gcool::sema::Sema& TheSema;
    gcool::sema::SemaScope* TheScope;
    ast::Class* SelfClass;
    SemaExprVisitor(gcool::sema::Sema& theSema, SemaScope* outerScope, ast::Class* selfClass)
        : TheSema(theSema), TheScope(outerScope), SelfClass(selfClass) {}
    
public:
    void operator()(Expr& ExprAnnot, ExprInt& expr) {
        auto annot = TheSema.allocAnnotation<ExprAnnotation>();
        annot->hasError = false;
        annot->Type = GETCLASS(SYMTBL.getInt());
        ExprAnnot.Annotation = annot;
    }

    void operator()(Expr& ExprAnnot, ExprFloat& expr) {
        auto annot = TheSema.allocAnnotation<ExprAnnotation>();
        annot->Type = GETCLASS(SYMTBL.getFloat());
        annot->hasError = false;
        ExprAnnot.Annotation = annot;
    }

    void operator()(Expr& ExprAnnot, ExprBool& expr) {
        auto annot = TheSema.allocAnnotation<ExprAnnotation>();
        annot->hasError = false;
        annot->Type = GETCLASS(SYMTBL.getBool());
        ExprAnnot.Annotation = annot;
    }

    void operator()(Expr& ExprAnnot, ExprString& expr) {
        auto annot = TheSema.allocAnnotation<ExprAnnotation>();
        annot->hasError = false;
        annot->Type = GETCLASS(SYMTBL.getString());
        ExprAnnot.Annotation = annot;
    }

    // check variable declaration, get Type/DeclRef
    void operator()(Expr& ExprAnnot, ExprSymbol& expr) {
        auto annot = TheSema.allocAnnotation<ExprSymbolAnnotation>();
        annot->hasError = false;
        auto decl = TheScope->searchVariable(expr.TheSymbol);
        if (!decl.Scope) {
            annot->hasError = true;
            TheSema.addError({basic::Diag::Sema_ExprSymbolNotDefine, 
                std::string(expr.TheSymbol.getName())});
        } else {
            annot->DeclRef = decl.Decl;
            annot->ScopeRef = decl.Scope;
            annot->Type = GETCLASS(decl.Decl->Type);
            if (!annot->Type) {
                annot->hasError = true;
                TheSema.addError({basic::Diag::Sema_ExprSymbolTypeError, 
                    std::string(decl.Decl->Type.getName())});
            }
        }
        ExprAnnot.Annotation = annot;
    }

    // check variable declaration, get Type
    // check ExprAnnot to assign
    void operator()(Expr& ExprAnnot, ExprAssign& expr) {
        auto annot = TheSema.allocAnnotation<ExprAnnotation>();
        annot->hasError = false;
        auto decl = TheScope->searchVariable(expr.Variable);
        if (!decl.Scope) {
            annot->hasError = true;
            TheSema.addError({basic::Diag::Sema_ExprAssignVariableNotDecl, 
                std::string(expr.Variable.getName())});
        } else {
            annot->Type = GETCLASS(decl.Decl->Type);
            if (!annot->Type) {
                annot->hasError = true;
                TheSema.addError({basic::Diag::Sema_ExprAssignVariableTypeError, 
                    std::string(decl.Decl->Type.getName())});
            }
        }

        expr.Value.accept(*this);
        if (expr.Value.Annotation->hasError) {
            annot->hasError = true;
            TheSema.addError({basic::Diag::Sema_ExprAssignExprError,
                std::string(expr.Variable.getName())});
        }

        if( !annot->hasError 
            && !TheSema.isSuper(annot->Type, expr.Value.Annotation->Type, SelfClass)) {
            annot->hasError = true;
            TheSema.addError({basic::Diag::Sema_ExprAssignTypeIncompatible,
                std::string(annot->Type->Name.getName()) + " <- " + 
                expr.Value.Annotation->Type->Name.getName().data()});
        }

        ExprAnnot.Annotation = annot;
    }
    
    // check callee Expr
    // check args Expr and args type
    // check method define, get Type
    void operator()(Expr& ExprAnnot, ExprDispatch& expr) {
        auto annot = TheSema.allocAnnotation<ExprDidpatchAnnotation>();
        annot->hasError = false;
        expr.Callee.accept(*this); 
        if (expr.Callee.Annotation->hasError) {
            annot->hasError = true;
            TheSema.addError({basic::Diag::Sema_ExprDispatchCalleeExprError, ""});
        }

        for( auto& e : expr.Args ) {
            e.accept(*this);
            if (e.Annotation->hasError) {
                annot->hasError = true;
                TheSema.addError({basic::Diag::Sema_ExprDispatchArgsExprError, ""});
            }
        }

        if (!annot->hasError) {
            auto c = expr.Callee.Annotation->Type;
            if (c->Name == SYMTBL.getSelfType())
                c = SelfClass;

            // check method decl
            auto methodDecl = c->Annotation->MTable.findMethod(expr.Method);
            auto method = methodDecl.Decl;
            if (!method) {
                annot->hasError = true;
                TheSema.addError({basic::Diag::Sema_ExprDispatchMethodUnknow, 
                    std::string(expr.Method.getName())});
                goto PARAM_CHECK_END;
            }
            annot->ClassRef = methodDecl.InClass;
            annot->MethodRef = method;
            if (method->RetType == SYMTBL.getSelfType())
                annot->Type = expr.Callee.Annotation->Type;
            else
                annot->Type = method->Annotation->RetClass;

            // check param and args
            if(method->FormalParams.size() != expr.Args.size()) {
                annot->hasError = true;
                TheSema.addError({basic::Diag::Sema_ExprDispatchArgsNumberError, 
                    std::string(expr.Method.getName())});
                goto PARAM_CHECK_END;
            }

            for(int i = 0; i < expr.Args.size(); ++i) {
                auto formalType = GETCLASS(method->FormalParams[i].Type);
                auto actualType = expr.Args[i].Annotation->Type;
                if (!TheSema.isSuper(formalType, actualType, SelfClass)) {
                    annot->hasError = true;
                    TheSema.addError({basic::Diag::Sema_ExprDispatchArgsTypeError, 
                        std::string(formalType->Name.getName()) + "<-" +
                        std::string(actualType->Name.getName())});
                }
            }
        }
        PARAM_CHECK_END:

        ExprAnnot.Annotation = annot;
    }

    // most copy from dispatch
    void operator()(Expr& ExprAnnot, ExprStaticDispatch& expr) {
        auto annot = TheSema.allocAnnotation<ExprDidpatchAnnotation>();
        expr.Callee.accept(*this);
        if (expr.Callee.Annotation->hasError) {
            annot->hasError = true;
            TheSema.addError({basic::Diag::Sema_ExprDispatchCalleeExprError, ""});
        }

        for( auto& e : expr.Args ) {
            e.accept(*this);
            if (e.Annotation->hasError) {
                annot->hasError = true;
                TheSema.addError({basic::Diag::Sema_ExprDispatchArgsExprError, ""});
            }
        }
        
        // static part
        auto c = GETCLASS(expr.Type);
        if (!c) {
            annot->hasError = true;
            TheSema.addError({basic::Diag::Sema_ExprStaticDispatchTypeUnkonw, 
                std::string(expr.Type.getName())});
        } else if (expr.Type == SYMTBL.getSelfType()) {
            annot->hasError = true;
            TheSema.addError({basic::Diag::Sema_ExprStaticDispatchTypeCantBeSelfType, 
                std::string(expr.Type.getName())});
        } else if (!TheSema.isSuper(c, expr.Callee.Annotation->Type, SelfClass)) {
            annot->hasError = true;
            TheSema.addError({basic::Diag::Sema_ExprStaticDispatchInheritError, 
                std::string(expr.Type.getName())});
        }

        if (!annot->hasError) {
            // check method decl
            auto methodDecl = c->Annotation->MTable.findMethodInClass(expr.Method);
            auto method = methodDecl.Decl;
            if (!method) {
                annot->hasError = true;
                TheSema.addError({basic::Diag::Sema_ExprDispatchMethodUnknow, 
                    std::string(expr.Method.getName())});
                goto PARAM_CHECK_END;
            }
            annot->ClassRef = methodDecl.InClass;
            annot->MethodRef = method;
            if (method->RetType == SYMTBL.getSelfType())
                annot->Type = expr.Callee.Annotation->Type;
            else
                annot->Type = method->Annotation->RetClass;

            if(method->FormalParams.size() != expr.Args.size()) {
                annot->hasError = true;
                TheSema.addError({basic::Diag::Sema_ExprDispatchArgsNumberError, 
                    std::string(expr.Method.getName())});
                goto PARAM_CHECK_END;
            }

            for(int i = 0; i < expr.Args.size(); ++i) {
                auto formalType = GETCLASS(method->FormalParams[i].Type);
                auto actualType = expr.Args[i].Annotation->Type;
                if (!TheSema.isSuper(formalType, actualType, SelfClass)) {
                    annot->hasError = true;
                    TheSema.addError({basic::Diag::Sema_ExprDispatchArgsTypeError, 
                        std::string(formalType->Name.getName()) + "<-" +
                        std::string(actualType->Name.getName())});
                }
            }
        }
        PARAM_CHECK_END:

        ExprAnnot.Annotation = annot;
    }

    void operator()(Expr& ExprAnnot, ExprCond& expr) {
        auto annot = TheSema.allocAnnotation<ExprAnnotation>();
        expr.Cond.accept(*this);
        expr.ThenBranch.accept(*this);
        expr.ElseBranch.accept(*this);
        if (expr.Cond.Annotation->hasError
            || expr.Cond.Annotation->Type->Name != SYMTBL.getBool()) {
            annot->hasError = true;
            TheSema.addError({basic::Diag::Sema_ExprCondConditionError, ""});
        }

        if (expr.ThenBranch.Annotation->hasError 
            || expr.ElseBranch.Annotation->hasError) {
            annot->hasError = true;
            TheSema.addError({basic::Diag::Sema_ExprCondBranchError, ""});
        } else {
            annot->Type = TheSema.getCommonSuper(
                expr.ThenBranch.Annotation->Type,
                expr.ElseBranch.Annotation->Type,
                SelfClass
                );
        }
        ExprAnnot.Annotation = annot;
    }

    void operator()(Expr& ExprAnnot, ExprLoop& expr) {
        auto annot = TheSema.allocAnnotation<ExprAnnotation>();
        expr.Cond.accept(*this);
        expr.LoopBody.accept(*this);
        if (expr.Cond.Annotation->hasError
            || expr.Cond.Annotation->Type->Name != SYMTBL.getBool()) {
            annot->hasError = true;
            TheSema.addError({basic::Diag::Sema_ExprLoopConditionError, ""});
        }

        if (expr.LoopBody.Annotation->hasError) {
            annot->hasError = true;
            TheSema.addError({basic::Diag::Sema_ExprLoopBodyError, ""});
        } else {
            annot->Type = expr.LoopBody.Annotation->Type;
        }
        ExprAnnot.Annotation = annot;
    }

    void operator()(Expr& ExprAnnot, ExprCase& expr) {
        auto annot = TheSema.allocAnnotation<ExprAnnotation>();
        
    }

    void operator()(Expr& ExprAnnot, ExprBlock& expr) {

    }

    void operator()(Expr& ExprAnnot, ExprLet& expr) {

    }

    void operator()(Expr& ExprAnnot, ExprNew& expr) {
        auto annot = TheSema.allocAnnotation<ExprAnnotation>();
        annot->hasError = false;
        annot->Type = GETCLASS(expr.Type);
        if (!annot->Type) {
            annot->hasError = true;
            TheSema.addError({basic::Diag::Sema_ExprNewTypeUndefine,
                std::string(expr.Type.getName())});
        }
        ExprAnnot.Annotation = annot;
    }

    void operator()(Expr& ExprAnnot, ExprSelf& expr) {
        auto annot = TheSema.allocAnnotation<ExprAnnotation>();
        annot->Type = GETCLASS(SYMTBL.getSelfType());
        annot->hasError = false;
        ExprAnnot.Annotation = annot;
    }

    void operator()(Expr& ExprAnnot, ExprArithB& expr) {

    }

    void operator()(Expr& ExprAnnot, ExprArithU& expr) {

    }
};

}

bool gcool::sema::Sema::checkExpr(ast::Expr& e, sema::SemaScope* scope, ast::Class* selfClass) {
    auto errorn = this->TheErrorList.size();
    SemaExprVisitor visitor(*this, scope, selfClass);
    e.accept(visitor);
    return this->TheErrorList.size() != errorn;
}

bool gcool::sema::Sema::isSuper(ast::Class* super, ast::Class* sub, ast::Class* selfClass) {
    if (super->Name == TheASTContext->Symtbl.getSelfType())
        return sub->Name == TheASTContext->Symtbl.getSelfType();
    if (sub->Name == TheASTContext->Symtbl.getSelfType())
        sub = selfClass;

    if (sub->Annotation->InheritDepth < super->Annotation->InheritDepth)
        return false;
    while (sub->Annotation->InheritDepth > super->Annotation->InheritDepth)
        sub = sub->Annotation->SuperClass;
    return super == sub;
}

gcool::ast::Class* gcool::sema::Sema::getCommonSuper(ast::Class* sub1, ast::Class* sub2, ast::Class* selfClass) {
    if (sub1 == sub2) 
        return sub1;
    if (sub1->Name == TheASTContext->Symtbl.getSelfType())
        sub1 = selfClass;
    else if (sub2->Name == TheASTContext->Symtbl.getSelfType())
        sub2 = selfClass;
    
    while (sub1->Annotation->InheritDepth < sub2->Annotation->InheritDepth)
        sub1 = sub1->Annotation->SuperClass;
    while (sub2->Annotation->InheritDepth < sub1->Annotation->InheritDepth)
        sub2 = sub2->Annotation->SuperClass;
    // 找到最近的公共超类, 至少返回 Object
    while (sub1 != sub2) {
        sub1 = sub1->Annotation->SuperClass;
        sub2 = sub2->Annotation->SuperClass;
    }
    return sub1;
}

void gcool::sema::Sema::addError(basic::Diag&& error) {
    TheErrorList.push_back(std::move(error));
}


#include "gcool/Sema/Sema.h"
#include "gcool/AST/Expr.h"
#include <unordered_map>
#include <stack>
#include <cassert>

using namespace gcool;
using namespace gcool::ast;
using namespace gcool::sema;

gcool::sema::Sema::~Sema() {
    for(auto p : this->AnnotationFreeList) 
        delete p;
}

bool gcool::sema::Sema::checkAll() {
    bool hasError = false;
    if (pass1())
        hasError = true;
    if (pass2())
        hasError = true;
    if (pass3())
        hasError = true;
    if (pass4())
        hasError = true;
    if (pass5())
        hasError = true;
    TheASTContext->Annotation->hasError = hasError;
    return hasError;
}

bool gcool::sema::Sema::pass1() {
    this->addBuiltinTypeAST();
    return false;
}

bool gcool::sema::Sema::pass2() {
    bool hasError = false;
    std::unordered_set<ast::Symbol> nameSet;
    // check for name multi defination, return hasError
    auto multiDefineCheck = [&nameSet](ast::Symbol s) -> bool {
        if (nameSet.find(s) != nameSet.end()) 
            return true;
        nameSet.insert(s);
        return false;
    };

    // construct Name Index Table
    // ClassName -> Class*
    // MethodName -> MethodFeature*
    // AttrName -> FormalDecl*
    TheASTContext->Annotation = allocAnnotation<ASTAnnotation>();
    for (auto& c : TheASTContext->Classes) {
        TheASTContext->Annotation->ClassMap.insert( {c.Name, &c} );
        c.Annotation = allocAnnotation<ClassAnnotation>();
        c.Annotation->MTable.InClass = &c;
        if (isBuiltinType(&c))
            c.Annotation->IsBuiltin = true;
        else 
            c.Annotation->IsBuiltin = false;

        nameSet.clear();
        for (auto& a : c.Attrs) {
            a.Annotation = allocAnnotation<AttrAnnotation>();
            if (multiDefineCheck(a.Formal.Name)) {
                hasError = true;
                a.Annotation->hasError = true;
                addError({basic::Diag::Sema_AttriMultiDefine, 
                    std::string(a.Formal.Name.getName())});
            }
            // c.Annotation->Scope.addVariable(a.Formal); in pass 5
        }

        nameSet.clear();
        for (auto& m : c.Methods) {
            m.Annotation = allocAnnotation<MethodAnnotation>();
            if (multiDefineCheck(m.Name)) {
                hasError = true;
                m.Annotation->hasError = true;
                addError({basic::Diag::Sema_MethodMultiDefine, 
                    std::string(m.Name.getName())});
            } else {
                c.Annotation->MTable.addMethod(m);
            }
        }
    }
    return hasError;
}

bool gcool::sema::Sema::pass3() {
    bool hasError = false;
    std::unordered_map<ast::Symbol, ast::Class*> classNameSet;
    for(auto& c : TheASTContext->Classes) {
        if (classNameSet.find(c.Name) != classNameSet.end()) {
            hasError = true;
            addError({basic::Diag::Sema_RedefineClass, 
                std::string(c.Name.getName())});
        } else {
            classNameSet.insert({c.Name, &c});
        }
    }

    auto root = TheASTContext->Annotation->findClass(
        TheASTContext->Symtbl.getObject()
    );
    assert(root && "must have object");
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
                if (super->IsFinal) {
                    c.Annotation->hasError = true;
                    addError({basic::Diag::Sema_InheritFromFinalClass, 
                        std::string(c.Name.getName())});
                }
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
            c.second->Annotation->hasError = true;
            addError({basic::Diag::Sema_LoopInherit, 
                std::string(c.first.getName())});
        }
    }
    return hasError;
}

bool gcool::sema::Sema::pass4() {
    bool hasError = false;
    for (auto& c : TheASTContext->Classes) {
        if (c.Annotation->hasError) continue;
        if (c.Name == TheASTContext->Symtbl.getSelfType()) continue;
        hasError = annotAttrDecl(&c) || hasError;
        hasError = annotMethodDecl(&c) || hasError;
    }
    return hasError;
}

bool gcool::sema::Sema::pass5() {
    bool hasError = false;
    for (auto& c : TheASTContext->Classes) {
        // class error are serious, stop sematic analysis
        if (c.Annotation->hasError) continue;
        // skip builtinType, their method body is empty
        if (c.Annotation->IsBuiltin)
            continue;

        for (auto& a : c.Attrs) {
            if (a.Init.has_value()){
                if (checkExpr(a.Init.value(), &c.Annotation->Scope, &c)){
                    a.Annotation->hasError = hasError = true;
                    addError({basic::Diag::Sema_DeclInitExprError, 
                        std::string(a.Formal.Name.getName())});
                } 
                
                if (!a.Annotation->hasError
                    && !isSuper(a.Annotation->DeclType, a.Init->Annotation->Type, &c)) {
                    a.Annotation->hasError = hasError = true;
                    addError({basic::Diag::Sema_DeclTypeIncompatible, 
                        std::string(a.Formal.Name.getName()) + "<-" +
                        std::string(a.Init->Annotation->Type->Name.getName())});
                }
            }
            // attr can use front attr to init
            c.Annotation->Scope.addVariable(a.Formal);
        }

        for (auto& m : c.Methods) {
            if (checkExpr(m.Body, &m.Annotation->MethodScope, &c)) {
                m.Annotation->hasError = hasError = true;
                addError({basic::Diag::Sema_MethodBodyExprError, 
                    std::string(m.Name.getName())});
            }
            
            if (!m.Annotation->hasError
                && !isSuper(m.Annotation->RetClassRef, m.Body.Annotation->Type, &c)) {
                m.Annotation->hasError = hasError = true;
                addError({basic::Diag::Sema_MethodBodyExprTypeIncompatible, 
                    std::string(m.RetType.getName()) + "<-" +
                    std::string(m.Body.Annotation->Type->Name.getName())});
            }
        }
    }
    return hasError;
}

bool gcool::sema::Sema::annotAttrDecl(ast::Class* Class) {
    bool hasError = false;

    int OffsetEnd = 1; // for objecy
    if (Class->Annotation->SuperClass != nullptr)
        OffsetEnd = Class->Annotation->SuperClass->Annotation->AttrOffsetEnd;
    
    for (auto& a : Class->Attrs) {
        a.Annotation->AttrOffset = OffsetEnd++;
        auto type = TheASTContext->Annotation->findClass(a.Formal.Type);
        if (!type || type->Annotation->hasError) {
            a.Annotation->hasError = hasError = true;
            addError({basic::Diag::Sema_DeclTypeError, 
                std::string(a.Formal.Type.getName())});
        } else {
            a.Annotation->DeclType = type;
        }
    }
    Class->Annotation->AttrOffsetEnd = OffsetEnd;
    return hasError;
}

bool gcool::sema::Sema::annotMethodDecl(ast::Class* Class) {
    bool hasError = false;
    ast::Class* superClass = Class->Annotation->SuperClass;
    int OffsetEnd = 0;
    if (superClass != nullptr)
        OffsetEnd = superClass->Annotation->MethodOffsetEnd; // method function table inherit from 

    for (auto& m : Class->Methods) {
        // check method return type
        m.Annotation->RetClassRef = TheASTContext->Annotation->findClass(m.RetType);
        if (!m.Annotation->RetClassRef || m.Annotation->RetClassRef->Annotation->hasError) {
            m.Annotation->hasError = true;
            addError({basic::Diag::Sema_MethodRetTypeError, std::string(m.RetType.getName())});
        }
        // check method params
        m.Annotation->MethodScope.OuterScope = &Class->Annotation->Scope;
        for (auto& f : m.FormalParams) {
            auto ft = TheASTContext->Annotation->findClass(f.Type);
            if (!ft || ft->Annotation->hasError) {
                m.Annotation->hasError = true;
                addError({basic::Diag::Sema_MethodParamTypeError, 
                    std::string(f.Type.getName())});
            } else if (f.Type == TheASTContext->Symtbl.getSelfType()) {
                m.Annotation->hasError = true;
                addError({basic::Diag::Sema_MethodParamCantBeSelfType, ""});
            }
            m.Annotation->MethodScope.addVariable(f);
        }

        // check override
        sema::MethodTable::MethodDecl superMDecl = {nullptr, nullptr};
        if (superClass != nullptr)
            superMDecl = superClass->Annotation->MTable.findMethod(m.Name);

        if (superMDecl.Decl == nullptr) {
            m.Annotation->MethodOffset = OffsetEnd++;
        } else {
            m.Annotation->MethodOffset = superMDecl.Decl->Annotation->MethodOffset;
            // check method override
            if (m.FormalParams.size() != superMDecl.Decl->FormalParams.size()) {
                m.Annotation->hasError = true;
                addError({basic::Diag::Sema_MethodOverrideDeclError, "number not match"});
            } else {
                for(int i = 0; i < m.FormalParams.size(); ++i) {
                    if (m.FormalParams[i].Type != superMDecl.Decl->FormalParams[i].Type) {
                        m.Annotation->hasError = true;
                        addError({basic::Diag::Sema_MethodOverrideDeclError, std::to_string(i)});
                    }
                }
            }
            if (m.RetType != superMDecl.Decl->RetType) {
                m.Annotation->hasError = true;
                addError({basic::Diag::Sema_MethodOverrideDeclError, "return type error"});
            }
        }
        hasError = hasError || m.Annotation->hasError;
    }
    Class->Annotation->MethodOffsetEnd = OffsetEnd;
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
    auto annot = TheSema.allocAnnotation<ExprIntAnnotation>();
    annot->hasError = false;
    annot->Type = GETCLASS(SYMTBL.getInt());
    ExprAnnot.Annotation = annot;
}

void operator()(Expr& ExprAnnot, ExprFloat& expr) {
    auto annot = TheSema.allocAnnotation<ExprFloatAnnotation>();
    annot->Type = GETCLASS(SYMTBL.getFloat());
    annot->hasError = false;
    ExprAnnot.Annotation = annot;
}

void operator()(Expr& ExprAnnot, ExprBool& expr) {
    auto annot = TheSema.allocAnnotation<ExprBoolAnnotation>();
    annot->hasError = false;
    annot->Type = GETCLASS(SYMTBL.getBool());
    ExprAnnot.Annotation = annot;
}

void operator()(Expr& ExprAnnot, ExprString& expr) {
    auto annot = TheSema.allocAnnotation<ExprStringAnnotation>();
    annot->hasError = false;
    annot->Type = GETCLASS(SYMTBL.getString());
    ExprAnnot.Annotation = annot;
}

// check variable declaration, get Type/DeclRef
void operator()(Expr& ExprAnnot, ExprSymbol& expr) {
    auto annot = TheSema.allocAnnotation<ExprSymbolAnnotation>();
    annot->hasError = false;
    auto decl = TheScope->findVariable(expr.TheSymbol);
    if (!decl.Scope) {
        annot->hasError = true;
        TheSema.addError({basic::Diag::Sema_ExprSymbolNotDefine, 
            std::string(expr.TheSymbol.getName())});
    } else {
        annot->DeclRef = decl.Decl;
        annot->ScopeRef = decl.Scope;
        annot->Type = GETCLASS(decl.Decl->Type);
        if (!annot->Type || annot->Type->Annotation->hasError) {
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
    auto annot = TheSema.allocAnnotation<ExprAssignAnnotation>();
    annot->hasError = false;
    auto decl = TheScope->findVariable(expr.Variable);
    if (!decl.Decl) {
        annot->hasError = true;
        TheSema.addError({basic::Diag::Sema_ExprAssignVariableNotDecl, 
            std::string(expr.Variable.getName())});
    } else {
        annot->Type = GETCLASS(decl.Decl->Type);
        annot->ScopeRef = decl.Scope;
        annot->DeclRef = decl.Decl;
        if (!annot->Type || annot->Type->Annotation->hasError) {
            annot->hasError = true;
            TheSema.addError({basic::Diag::Sema_ExprAssignVariableTypeError, 
                std::string(expr.Variable.getName())});
        }
    }

    expr.Value.accept(*this);
    if (expr.Value.Annotation->hasError) {
        annot->hasError = true;
        TheSema.addError({basic::Diag::Sema_ExprAssignExprError, ""});
    }

    if (!annot->hasError
        && !TheSema.isSuper(annot->Type, expr.Value.Annotation->Type, SelfClass)) {
        annot->hasError = true;
        TheSema.addError({basic::Diag::Sema_ExprAssignTypeIncompatible, 
            std::string(annot->Type->Name.getName()) + "<-" +
            std::string(expr.Value.Annotation->Type->Name.getName())});
    }

    ExprAnnot.Annotation = annot;
}

void checkCalleeAndArgs(ExprDispatchAnnotation* annot, Expr& Callee, ExprList& Args) {
    Callee.accept(*this); 
    if (Callee.Annotation->hasError) {
        annot->hasError = true;
        TheSema.addError({basic::Diag::Sema_ExprDispatchCalleeExprError, ""});
    }
    for( auto& e : Args ) {
        e.accept(*this);
        if (e.Annotation->hasError) {
            annot->hasError = true;
            TheSema.addError({basic::Diag::Sema_ExprDispatchArgsExprError, ""});
        }
    }
}

void findMethodAndCheckParam(ExprDispatchAnnotation* annot, Expr& Callee, ExprList& Args
    , ast::Symbol Method, ast::Class* c) {
    auto methodDecl = c->Annotation->MTable.findMethod(Method);
    auto method = methodDecl.Decl;
    if (!method) {
        annot->hasError = true;
        TheSema.addError({basic::Diag::Sema_ExprDispatchMethodUnknow, 
            std::string(Method.getName())});
        return;
    }
    annot->ClassRef = methodDecl.InClass;
    annot->MethodRef = method;
    if (method->RetType == SYMTBL.getSelfType())
        annot->Type = Callee.Annotation->Type;
    else
        annot->Type = method->Annotation->RetClassRef;
    
    // error decl method
    if (method->Annotation->hasError) {
        annot->hasError = true;
        TheSema.addError({basic::Diag::Sema_ExprDispatchMethodDeclError,
            std::string(Method.getName())});
        return;
    }

    // check params number
    if(method->FormalParams.size() != Args.size()) {
        annot->hasError = true;
        TheSema.addError({basic::Diag::Sema_ExprDispatchArgsNumberError, 
            std::string(Method.getName())});
        return;
    }
    // check param and args
    for(int i = 0; i < Args.size(); ++i) {
        auto formalType = GETCLASS(method->FormalParams[i].Type);
        auto actualType = Args[i].Annotation->Type;
        assert(formalType && "alreay check in Sema_ExprDispatchMethodDeclError");
        if (!TheSema.isSuper(formalType, actualType, SelfClass)) {
            annot->hasError = true;
            TheSema.addError({basic::Diag::Sema_ExprDispatchArgsTypeError, 
                std::string(formalType->Name.getName()) + "<-" +
                std::string(actualType->Name.getName())});
        }
    }
}

// check callee Expr
// check args Expr and args type
// check method define, get Type
void operator()(Expr& ExprAnnot, ExprDispatch& expr) {
    auto annot = TheSema.allocAnnotation<ExprDispatchAnnotation>();
    annot->hasError = false;
    checkCalleeAndArgs(annot, expr.Callee, expr.Args);

    if (!annot->hasError) {
        auto c = expr.Callee.Annotation->Type;
        if (c->Name == SYMTBL.getSelfType())
            c = SelfClass;

        findMethodAndCheckParam(annot, expr.Callee, expr.Args,
            expr.Method, c);
    }

    ExprAnnot.Annotation = annot;
}

void operator()(Expr& ExprAnnot, ExprStaticDispatch& expr) {
    auto annot = TheSema.allocAnnotation<ExprStaticDispatchAnnotation>();
    annot->hasError = false;
    checkCalleeAndArgs(annot, expr.Callee, expr.Args);
    
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
        findMethodAndCheckParam(annot, expr.Callee, expr.Args,
            expr.Method, c);
    }

    ExprAnnot.Annotation = annot;
}

void operator()(Expr& ExprAnnot, ExprCond& expr) {
    auto annot = TheSema.allocAnnotation<ExprCondAnnotation>();
    annot->hasError = false;
    expr.Cond.accept(*this);
    if (expr.Cond.Annotation->hasError
        || expr.Cond.Annotation->Type->Name != SYMTBL.getBool()) {
        annot->hasError = true;
        TheSema.addError({basic::Diag::Sema_ExprCondConditionError, ""});
    }
    expr.ThenBranch.accept(*this);
    expr.ElseBranch.accept(*this);
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
    auto annot = TheSema.allocAnnotation<ExprLoopAnnotation>();
    annot->hasError = false;
    expr.Cond.accept(*this);
    if (expr.Cond.Annotation->hasError
        || expr.Cond.Annotation->Type->Name != SYMTBL.getBool()) {
        annot->hasError = true;
        TheSema.addError({basic::Diag::Sema_ExprLoopConditionError, ""});
    }
    expr.LoopBody.accept(*this);
    if (expr.LoopBody.Annotation->hasError) {
        annot->hasError = true;
        TheSema.addError({basic::Diag::Sema_ExprLoopBodyError, ""});
    }
    annot->Type = expr.LoopBody.Annotation->Type;
    ExprAnnot.Annotation = annot;
}

void operator()(Expr& ExprAnnot, ExprCase& expr) {
    auto annot = TheSema.allocAnnotation<ExprCaseAnnotation>();
    annot->hasError = false;
    expr.Cond.accept(*this);
    if (expr.Cond.Annotation->hasError) {
        annot->hasError = true;
        TheSema.addError({basic::Diag::Sema_ExprCaseCondExprError, ""});    
    }
    annot->Type = nullptr;
    annot->BranchScope.resize(expr.Branchs.size(), {TheScope, SemaScope::SK_Local});
    for (int i = 0; i < expr.Branchs.size(); ++i) {
        auto&b = expr.Branchs[i];
        auto&branchScope = annot->BranchScope[i];

        auto c = GETCLASS(b.Formal.Name);
        if (!c) {
            annot->hasError = true;
            TheSema.addError({basic::Diag::Sema_ExprCaseBrachTypeUnkonw, 
                std::string(b.Formal.Type.getName())});  
        } else {
            branchScope.addVariable(b.Formal);
            auto outerScope = TheScope;
            TheScope = &branchScope;
            b.Body.accept(*this);
            TheScope = outerScope;
            if (b.Body.Annotation->hasError) {
                annot->hasError = true;
                TheSema.addError({basic::Diag::Sema_ExprCaseBrachExprError, 
                    std::string(b.Formal.Name.getName())});  
            } else if (annot->Type == nullptr) {
                annot->Type = b.Body.Annotation->Type;
            } else {
                annot->Type = TheSema.getCommonSuper(
                    annot->Type, b.Body.Annotation->Type, SelfClass);
            }
        }
    }
    ExprAnnot.Annotation = annot;
}

void operator()(Expr& ExprAnnot, ExprBlock& expr) {
    auto annot = TheSema.allocAnnotation<ExprBlockAnnotation>();
    annot->hasError = false;
    annot->Type = nullptr;
    int i = 0;
    for (auto& e : expr.Exprs) {
        e.accept(*this);
        if (e.Annotation->hasError) {
            annot->hasError = true;
            TheSema.addError({basic::Diag::Sema_ExprBlockExprError, 
                "order=" + std::to_string(i)});  
        } 
        annot->Type = e.Annotation->Type;
        ++i;
    }
    ExprAnnot.Annotation = annot;
}

void operator()(Expr& ExprAnnot, ExprLet& expr) {
    auto annot = TheSema.allocAnnotation<ExprLetAnnotation>();
    annot->hasError = false;
    std::unordered_set<ast::Symbol> nameset;
    auto outerScope = TheScope;
    TheScope = &annot->LocalScope;
    for(auto& decl : expr.InitVariables) {
        bool declError = false;
        if (nameset.find(decl.Formal.Name) != nameset.end()) {
            annot->hasError = true;
            TheSema.addError({basic::Diag::Sema_ExprLetInitMultiDefine, 
                std::string(decl.Formal.Name.getName())});  
        } else {
            nameset.insert(decl.Formal.Name);
            auto c = GETCLASS(decl.Formal.Type);
            if (!c || c->Annotation->hasError) {
                annot->hasError = declError = true;
                TheSema.addError({basic::Diag::Sema_ExprLetInitDeclTypeError, 
                    std::string(decl.Formal.Name.getName())});  
            } 
            
            if (decl.Init.has_value()) {
                auto& e = decl.Init.value();
                e.accept(*this);
                if (e.Annotation->hasError) {
                    annot->hasError = declError = true;
                    TheSema.addError({basic::Diag::Sema_ExprLetInitDeclExprError, ""});  
                } else if (!declError 
                    && !TheSema.isSuper(c, e.Annotation->Type, SelfClass)) {
                    annot->hasError = declError = true;
                    TheSema.addError({basic::Diag::Sema_ExprLetInitDeclExprIncompatible, 
                        std::string(c->Name.getName()) + "<-" +
                        std::string(e.Annotation->Type->Name.getName())});
                }
            }
            annot->LocalScope.addVariable(decl.Formal);
        }
    }

    expr.LetBody.accept(*this);
    TheScope = outerScope;

    annot->Type = expr.LetBody.Annotation->Type;
    if (expr.LetBody.Annotation->hasError) {
        annot->hasError = true;
        TheSema.addError({basic::Diag::Sema_ExprLetBodyExprError, ""});  
    }

    ExprAnnot.Annotation = annot;
}

void operator()(Expr& ExprAnnot, ExprNew& expr) {
    auto annot = TheSema.allocAnnotation<ExprNewAnnotation>();
    annot->hasError = false;
    annot->Type = GETCLASS(expr.Type);
    if (!annot->Type) {
        annot->hasError = true;
        TheSema.addError({basic::Diag::Sema_ExprNewTypeUndefine,
            std::string(expr.Type.getName())});
    } else if (annot->Type->Name == SYMTBL.getSelfType()) {
        annot->IsSelfType = true;
    } else {
        annot->IsSelfType = false;
    }
    ExprAnnot.Annotation = annot;
}

void operator()(Expr& ExprAnnot, ExprSelf& expr) {
    auto annot = TheSema.allocAnnotation<ExprSelfAnnotation>();
    annot->hasError = false;
    annot->Type = GETCLASS(SYMTBL.getSelfType());
    ExprAnnot.Annotation = annot;
}

void operator()(Expr& ExprAnnot, ExprArithB& expr) {
    auto annot = TheSema.allocAnnotation<ExprArithBAnnotation>();
    annot->hasError = false;
    expr.Left.accept(*this);
    if (expr.Left.Annotation->hasError) {
        annot->hasError = true;
        TheSema.addError({basic::Diag::Sema_ExprArithBLeftExprError, ""});
    }
    expr.Right.accept(*this);
    if (expr.Right.Annotation->hasError) {
        annot->hasError = true;
        TheSema.addError({basic::Diag::Sema_ExprArithBRightExprError, ""});
    }

    if (!annot->hasError) {
        auto funcName = ast::ExprArithB::OverloadFuncName[expr.Operator];
        auto overloadF = expr.Left.Annotation->Type->Annotation->MTable.findMethod(SYMTBL.get(funcName));
        if (!overloadF.Decl) {
            annot->hasError = true;
            this->TheSema.addError({basic::Diag::Sema_ExprArithBNoOverloadFunc, funcName});
            goto CHECK_BREAK;
        } else {
            annot->ClassRef = overloadF.InClass;
            annot->MethodRef = overloadF.Decl;
            annot->Type = overloadF.Decl->Annotation->RetClassRef;
        } 
        if (overloadF.Decl->Annotation->hasError) {
            annot->hasError = true;
            this->TheSema.addError({basic::Diag::Sema_ExprArithBOverloadFuncError, funcName});
            goto CHECK_BREAK;
        }
        if (overloadF.Decl->FormalParams.size() != 1) {
            annot->hasError = true;
            this->TheSema.addError({basic::Diag::Sema_ExprArithBOverloadFuncArgsTypeIncompatible, funcName});
            goto CHECK_BREAK;
        }
        auto formalType = GETCLASS(overloadF.Decl->FormalParams[0].Type);
        if ( !TheSema.isSuper(formalType, expr.Right.Annotation->Type, SelfClass)) {
            annot->hasError = true;
            this->TheSema.addError({basic::Diag::Sema_ExprArithBOverloadFuncArgsTypeIncompatible, funcName});
        }
    }
    CHECK_BREAK:
    ExprAnnot.Annotation = annot;
}

void operator()(Expr& ExprAnnot, ExprArithU& expr) {
    auto annot = TheSema.allocAnnotation<ExprArithUAnnotation>();
    annot->hasError = false;
    expr.Operand.accept(*this);
    if (expr.Operand.Annotation->hasError) {
        annot->hasError = true;
        TheSema.addError({basic::Diag::Sema_ExprArithUOperandExprError, ""});
    }

    if (!annot->hasError) {
        auto funcName = ast::ExprArithU::OverloadFuncName[expr.Operator];
        auto overloadF = expr.Operand.Annotation->Type->Annotation->MTable.findMethod(SYMTBL.get(funcName));
        if (!overloadF.Decl) {
            annot->hasError = true;
            this->TheSema.addError({basic::Diag::Sema_ExprArithUNoOverloadFunc, funcName});
            goto CHECK_BREAK;
        } else {
            annot->ClassRef = overloadF.InClass;
            annot->MethodRef = overloadF.Decl;
            annot->Type = overloadF.Decl->Annotation->RetClassRef;
        } 
        if (overloadF.Decl->Annotation->hasError) {
            annot->hasError = true;
            this->TheSema.addError({basic::Diag::Sema_ExprArithUOverloadFuncError, funcName});
            goto CHECK_BREAK;
        }
        if (overloadF.Decl->FormalParams.size() != 0) {
            annot->hasError = true;
            this->TheSema.addError({basic::Diag::Sema_ExprArithUOverloadFuncArgsTypeeIncompatible, funcName});
        }
    }
    CHECK_BREAK:
    ExprAnnot.Annotation = annot;
}

};

}

bool gcool::sema::Sema::checkExpr(ast::Expr& e, sema::SemaScope* scope, ast::Class* selfClass) {
    SemaExprVisitor visitor(*this, scope, selfClass);
    e.accept(visitor);
    return e.Annotation->hasError;
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

bool gcool::sema::Sema::isBuiltinType(ast::Class* c) {
    if (c->Name == TheASTContext->Symtbl.getObject()
        || c->Name == TheASTContext->Symtbl.getSelfType()
        || c->Name == TheASTContext->Symtbl.getInt()
        || c->Name == TheASTContext->Symtbl.getFloat()
        || c->Name == TheASTContext->Symtbl.getBool()
        || c->Name == TheASTContext->Symtbl.getString())
        return true;
    else
        return false;
}

// builtinType, and builtinFunction
// funcname 0 start(such as 0new) is builtin function that programer can't call and overload
void gcool::sema::Sema::addBuiltinTypeAST() {
    auto& sym = TheASTContext->Symtbl;
    auto exprHolder = TheASTContext->ExprAlloc.allocExpr(ast::ExprString("builtin"));
    // TODO
    TheASTContext->Classes.push_back( 
        Class{TheASTContext->Symtbl.getObject(),
            {},
            {MethodFeature{sym.get("0new"), sym.getSelfType(), FormalList{}, exprHolder},
             MethodFeature{sym.get("opisvoid"), sym.getBool(), FormalList{}, exprHolder}
            },
            Symbol::EmptySymbol
            } );
    TheASTContext->Classes.push_back( 
        Class{TheASTContext->Symtbl.getInt(), 
            {AttrFeature{FormalDecl{sym.get("IntValue"), sym.getObject()}, {}}}, 
            {MethodFeature{sym.get("opadd"), sym.getInt(), FormalList{FormalDecl{sym.get("right"), sym.getInt()}}, exprHolder},
             MethodFeature{sym.get("opsub"), sym.getInt(), FormalList{FormalDecl{sym.get("right"), sym.getInt()}}, exprHolder},
             MethodFeature{sym.get("opmul"), sym.getInt(), FormalList{FormalDecl{sym.get("right"), sym.getInt()}}, exprHolder},
             MethodFeature{sym.get("opdiv"), sym.getInt(), FormalList{FormalDecl{sym.get("right"), sym.getInt()}}, exprHolder},
             MethodFeature{sym.get("opeq"), sym.getBool(), FormalList{FormalDecl{sym.get("right"), sym.getInt()}}, exprHolder},
             MethodFeature{sym.get("opge"), sym.getBool(), FormalList{FormalDecl{sym.get("right"), sym.getInt()}}, exprHolder},
             MethodFeature{sym.get("opgt"), sym.getBool(), FormalList{FormalDecl{sym.get("right"), sym.getInt()}}, exprHolder},
             MethodFeature{sym.get("ople"), sym.getBool(), FormalList{FormalDecl{sym.get("right"), sym.getInt()}}, exprHolder},
             MethodFeature{sym.get("oplt"), sym.getBool(), FormalList{FormalDecl{sym.get("right"), sym.getInt()}}, exprHolder}
            },
            TheASTContext->Symtbl.getObject(), true} );
    TheASTContext->Classes.push_back( 
        Class{TheASTContext->Symtbl.getFloat(), 
            {AttrFeature{FormalDecl{sym.get("FloatValue"), sym.getObject()}, {}}}, 
            {MethodFeature{sym.get("opadd"), sym.getFloat(), FormalList{FormalDecl{sym.get("right"), sym.getFloat()}}, exprHolder},
             MethodFeature{sym.get("opsub"), sym.getFloat(), FormalList{FormalDecl{sym.get("right"), sym.getFloat()}}, exprHolder},
             MethodFeature{sym.get("opmul"), sym.getFloat(), FormalList{FormalDecl{sym.get("right"), sym.getFloat()}}, exprHolder},
             MethodFeature{sym.get("opdiv"), sym.getFloat(), FormalList{FormalDecl{sym.get("right"), sym.getFloat()}}, exprHolder},
             MethodFeature{sym.get("opeq"), sym.getBool(), FormalList{FormalDecl{sym.get("right"), sym.getFloat()}}, exprHolder},
             MethodFeature{sym.get("opge"), sym.getBool(), FormalList{FormalDecl{sym.get("right"), sym.getFloat()}}, exprHolder},
             MethodFeature{sym.get("opgt"), sym.getBool(), FormalList{FormalDecl{sym.get("right"), sym.getFloat()}}, exprHolder},
             MethodFeature{sym.get("ople"), sym.getBool(), FormalList{FormalDecl{sym.get("right"), sym.getFloat()}}, exprHolder},
             MethodFeature{sym.get("oplt"), sym.getBool(), FormalList{FormalDecl{sym.get("right"), sym.getFloat()}}, exprHolder}
            },
            TheASTContext->Symtbl.getObject(), true} );
    TheASTContext->Classes.push_back( 
        Class{TheASTContext->Symtbl.getBool(), 
            {AttrFeature{FormalDecl{sym.get("BoolValue"), sym.getObject()}, {}}}, 
            {MethodFeature{sym.get("opadd"), sym.getBool(), FormalList{FormalDecl{sym.get("right"), sym.getBool()}}, exprHolder},
             MethodFeature{sym.get("opmul"), sym.getBool(), FormalList{FormalDecl{sym.get("right"), sym.getBool()}}, exprHolder},
             MethodFeature{sym.get("opeq"), sym.getBool(), FormalList{FormalDecl{sym.get("right"), sym.getBool()}}, exprHolder},
             MethodFeature{sym.get("opnot"), sym.getBool(), FormalList{}, exprHolder}
            },
            TheASTContext->Symtbl.getObject(), true} );
    TheASTContext->Classes.push_back( 
        Class{TheASTContext->Symtbl.getString(), 
            {AttrFeature{FormalDecl{sym.get("StringValue"), sym.getObject()}, {}}}, 
            {MethodFeature{sym.get("opadd"), sym.getString(), FormalList{FormalDecl{sym.get("right"), sym.getString()}}, exprHolder},
             MethodFeature{sym.get("opeq"), sym.getBool(), FormalList{FormalDecl{sym.get("right"), sym.getString()}}, exprHolder},
             MethodFeature{sym.get("opge"), sym.getBool(), FormalList{FormalDecl{sym.get("right"), sym.getString()}}, exprHolder},
             MethodFeature{sym.get("opgt"), sym.getBool(), FormalList{FormalDecl{sym.get("right"), sym.getString()}}, exprHolder},
             MethodFeature{sym.get("ople"), sym.getBool(), FormalList{FormalDecl{sym.get("right"), sym.getString()}}, exprHolder},
             MethodFeature{sym.get("oplt"), sym.getBool(), FormalList{FormalDecl{sym.get("right"), sym.getString()}}, exprHolder}
            },
            TheASTContext->Symtbl.getObject(), true} );
    
    // abstract class, make code simplifiy
    TheASTContext->Classes.push_back( 
        Class{TheASTContext->Symtbl.getSelfType(), Symbol::EmptySymbol} );
}

void gcool::sema::Sema::addError(basic::Diag&& error) {
    TheErrorList.push_back(std::move(error));
}


#include "gcool/Sema/Sema.h"
#include "gcool/AST/Expr.h"
#include <unordered_map>
#include <stack>
#include <cassert>

using namespace gcool;
using namespace gcool::sema;
using namespace gcool::ast;

namespace {

#define SYMTBL TheSema.TheASTContext->Symtbl
#define GETCLASS(Sym) TheSema.TheASTContext->Annotation->findClass(Sym)

#define UPDATELOCALVARN(newMax) *LocalVarN = std::max(*LocalVarN, newMax)

class SemaExprVisitor : public gcool::ast::ExprVisitor {
public:
    gcool::sema::Sema& TheSema;
    gcool::sema::SemaScope* TheScope;
    ast::Class* SelfClass;
    int* LocalVarN;
    SemaExprVisitor(gcool::sema::Sema& theSema, SemaScope* outerScope, ast::Class* selfClass, int* localvarN)
        : TheSema(theSema), TheScope(outerScope), SelfClass(selfClass), LocalVarN(localvarN) {}
    
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
        annot->Offset = decl.Offset;
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
        annot->Offset = decl.Offset;
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
    annot->StaticMethodClassRef = methodDecl.InClass;
    annot->StaticMethodRef = method;
    if (method->RetType == SYMTBL.getSelfType())
        annot->Type = Callee.Annotation->Type;
    else
        annot->Type = GETCLASS(method->RetType);
    
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

        auto c = GETCLASS(b.Formal.Type);
        if (!c) {
            annot->hasError = true;
            TheSema.addError({basic::Diag::Sema_ExprCaseBrachTypeUnkonw, 
                std::string(b.Formal.Type.getName())});  
        } else {
            branchScope.addVariable(b.Formal);
            auto outerScope = TheScope;
            TheScope = &branchScope;
            b.Body.accept(*this);
            UPDATELOCALVARN(TheScope->getLocalVarN());
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
    annot->LocalScope.setOuter(TheScope);
    auto outerScope = TheScope;
    TheScope = &annot->LocalScope;
    std::unordered_set<ast::Symbol> nameset;
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
    UPDATELOCALVARN(TheScope->getLocalVarN());
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

void operator()(Expr& ExprAnnot, ExprNull& expr) {
    auto annot = TheSema.allocAnnotation<ExprNullAnnotation>();
    annot->hasError = false;
    annot->Type = GETCLASS(SYMTBL.getNullType());
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
            annot->StaticMethodClassRef = overloadF.InClass;
            annot->StaticMethodRef = overloadF.Decl;
            annot->Type = GETCLASS(overloadF.Decl->RetType);
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
            annot->StaticMethodClassRef = overloadF.InClass;
            annot->StaticMethodRef = overloadF.Decl;
            annot->Type = GETCLASS(overloadF.Decl->RetType);
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

bool gcool::sema::Sema::checkExpr(ast::Expr& e, sema::SemaScope* scope, ast::Class* selfClass, int* LocalVarN) {
    SemaExprVisitor visitor(*this, scope, selfClass, LocalVarN);
    e.accept(visitor);
    return e.Annotation->hasError;
}

#include "gcool/Sema/Sema.h"
#include "gcool/AST/Expr.h"
#include <stack>
#include <cassert>

using namespace gcool;

#define GETCLASS TheASTContext->Annotation->findClass
#define SYMTBL TheASTContext->Symtbl

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
        annotClassKind(&c);

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
            m.Annotation->InClass = &c;
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

    auto root = GETCLASS(
        SYMTBL.getObject()
    );
    assert(root && "must have object");
    root->Annotation->SuperClass = nullptr;
    root->Annotation->InheritDepth = 0;
    classNameSet.erase(root->Name);
    classNameSet.erase(SYMTBL.getSelfType()); // Inherit from SelfType is forbid
    classNameSet.erase(SYMTBL.getNullType()); // can't inherit from abstract class
    TheASTContext->Annotation->InheritOrder.push_back(root);
    std::stack<ast::Class*> parent;
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
                TheASTContext->Annotation->InheritOrder.push_back(&c);
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
    for (auto* c : TheASTContext->Annotation->InheritOrder) {
        hasError = annotAttrDecl(c) || hasError;
        hasError = annotMethodDecl(c) || hasError;
    }
    return hasError;
}

bool gcool::sema::Sema::pass5() {
    bool hasError = false;
    for (auto& c : TheASTContext->Classes) {
        // class error are serious, stop sematic analysis
        if (c.Annotation->hasError) continue;
        // skip builtinType, their method body is empty
        if (c.Annotation->TheClassKind != sema::ClassAnnotation::CK_Trivial)
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
                && !isSuper(GETCLASS(m.RetType), m.Body.Annotation->Type, &c)) {
                m.Annotation->hasError = hasError = true;
                addError({basic::Diag::Sema_MethodBodyExprTypeIncompatible, 
                    std::string(m.RetType.getName()) + "<-" +
                    std::string(m.Body.Annotation->Type->Name.getName())});
            }
        }
    }
    return hasError;
}

void gcool::sema::Sema::annotClassKind(ast::Class* c) {
    if (c->Name == SYMTBL.getObject())
        c->Annotation->TheClassKind = sema::ClassAnnotation::CK_Object;
    else if (c->Name == SYMTBL.getInt()
        || c->Name == SYMTBL.getFloat()
        || c->Name == SYMTBL.getBool()
        || c->Name == SYMTBL.getString())
        c->Annotation->TheClassKind = sema::ClassAnnotation::CK_Primitive;
    else if (c->Name == SYMTBL.getSelfType()
        || c->Name == SYMTBL.getNullType())
        c->Annotation->TheClassKind = sema::ClassAnnotation::CK_Abstract;
    else
        c->Annotation->TheClassKind = sema::ClassAnnotation::CK_Trivial;
}

bool gcool::sema::Sema::annotAttrDecl(ast::Class* Class) {
    bool hasError = false;

    int OffsetEnd = 0; // Object
    if (Class->Annotation->SuperClass != nullptr)
        OffsetEnd = Class->Annotation->SuperClass->Annotation->AttrOffsetEnd;
    
    for (auto& a : Class->Attrs) {
        a.Annotation->AttrOffset = OffsetEnd++;
        auto type = GETCLASS(a.Formal.Type);
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

// follow inherit Order
bool gcool::sema::Sema::annotMethodDecl(ast::Class* Class) {
    bool hasError = false;
    ast::Class* superClass = Class->Annotation->SuperClass;

    int OffsetEnd = 0; // Obejct
    if (superClass != nullptr)
        OffsetEnd = superClass->Annotation->MethodOffsetEnd; // method function table inherit from 

    for (auto& m : Class->Methods) {
        // check method return type
        auto retType = GETCLASS(m.RetType);
        if (!retType || retType->Annotation->hasError) {
            m.Annotation->hasError = true;
            addError({basic::Diag::Sema_MethodRetTypeError, std::string(m.RetType.getName())});
        }
        // check method params
        m.Annotation->MethodScope.setOuter(&Class->Annotation->Scope);
        for (auto& f : m.FormalParams) {
            auto ft = GETCLASS(f.Type);
            if (!ft || ft->Annotation->hasError) {
                m.Annotation->hasError = true;
                addError({basic::Diag::Sema_MethodParamTypeError, 
                    std::string(f.Type.getName())});
            } else if (f.Type == SYMTBL.getSelfType()) {
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

bool gcool::sema::Sema::isSuper(ast::Class* super, ast::Class* sub, ast::Class* selfClass) {
    assert((super->Name != SYMTBL.getNullType()) && "can't assign to null type");
    // null can assign to any class
    if (sub->Name == SYMTBL.getNullType())
        return true;
    if (super->Name == SYMTBL.getSelfType())
        return sub->Name == SYMTBL.getSelfType();
    if (sub->Name == SYMTBL.getSelfType())
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
    if (sub1->Name == SYMTBL.getSelfType())
        sub1 = selfClass;
    else if (sub2->Name == SYMTBL.getSelfType())
        sub2 = selfClass;
    else if (sub1->Name == SYMTBL.getNullType())
        return sub2;
    else if (sub2->Name == SYMTBL.getNullType())
        return sub1;
    
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

using namespace ast;

// builtinType, and builtinFunction
// funcname 0 start(such as 0new) is builtin function that programer can't call and overload
void gcool::sema::Sema::addBuiltinTypeAST() {
    auto& sym = SYMTBL;
    auto exprHolder = TheASTContext->ExprAlloc.allocExpr(ast::ExprString("builtin"));
    TheASTContext->Classes.push_back( 
        Class{SYMTBL.getObject(),
            {},
            {MethodFeature{sym.getNewMethod(), sym.getSelfType(), FormalList{}, exprHolder},
             MethodFeature{sym.get("opisvoid"), sym.getBool(), FormalList{}, exprHolder}
            },
            Symbol::EmptySymbol
            } );
    TheASTContext->Classes.push_back( 
        Class{SYMTBL.getInt(), 
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
            SYMTBL.getObject(), true} );
    TheASTContext->Classes.push_back( 
        Class{SYMTBL.getFloat(), 
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
            SYMTBL.getObject(), true} );
    TheASTContext->Classes.push_back( 
        Class{SYMTBL.getBool(), 
            {AttrFeature{FormalDecl{sym.get("BoolValue"), sym.getObject()}, {}}}, 
            {MethodFeature{sym.get("opadd"), sym.getBool(), FormalList{FormalDecl{sym.get("right"), sym.getBool()}}, exprHolder},
             MethodFeature{sym.get("opmul"), sym.getBool(), FormalList{FormalDecl{sym.get("right"), sym.getBool()}}, exprHolder},
             MethodFeature{sym.get("opeq"), sym.getBool(), FormalList{FormalDecl{sym.get("right"), sym.getBool()}}, exprHolder},
             MethodFeature{sym.get("opnot"), sym.getBool(), FormalList{}, exprHolder}
            },
            SYMTBL.getObject(), true} );
    TheASTContext->Classes.push_back( 
        Class{SYMTBL.getString(), 
            {AttrFeature{FormalDecl{sym.get("StringValue"), sym.getObject()}, {}}}, 
            {MethodFeature{sym.get("opadd"), sym.getString(), FormalList{FormalDecl{sym.get("right"), sym.getString()}}, exprHolder},
             MethodFeature{sym.get("opeq"), sym.getBool(), FormalList{FormalDecl{sym.get("right"), sym.getString()}}, exprHolder},
             MethodFeature{sym.get("opge"), sym.getBool(), FormalList{FormalDecl{sym.get("right"), sym.getString()}}, exprHolder},
             MethodFeature{sym.get("opgt"), sym.getBool(), FormalList{FormalDecl{sym.get("right"), sym.getString()}}, exprHolder},
             MethodFeature{sym.get("ople"), sym.getBool(), FormalList{FormalDecl{sym.get("right"), sym.getString()}}, exprHolder},
             MethodFeature{sym.get("oplt"), sym.getBool(), FormalList{FormalDecl{sym.get("right"), sym.getString()}}, exprHolder}
            },
            SYMTBL.getObject(), true} );
    
    // abstract class, make code simplifiy
    TheASTContext->Classes.push_back( 
        Class{SYMTBL.getSelfType(), Symbol::EmptySymbol} );
    TheASTContext->Classes.push_back( 
        Class{SYMTBL.getNullType(), Symbol::EmptySymbol} );
}

void gcool::sema::Sema::addError(basic::Diag&& error) {
    TheErrorList.push_back(std::move(error));
}


#include "gcool/PrettyPrinter/ASTPrinter.h"
#include "gcool/AST/Expr.h"
#include "gcool/Sema/Sema.h"
#include "llvm/Support/raw_ostream.h"

using namespace gcool;

#define NEXTLINE os << "\n"
#define INDENT printIndent(os)
#define INCINDENT ++Indent
#define DECINDENT --Indent
#define ANNOT(annot) (annot->hasError ? "annot: hasError=true; " : "annot: hasError=false; ")
#define FORMAL(f)  f.Name.getName() << " : " << f.Type.getName()

// 每个函数默认开始不换行，结尾换行

void pretty::ASTPrinter::printIndent(llvm::raw_ostream& os) {
    auto spaces = Indent * IndentSpace;
    for (int i = 0; i < spaces; ++i)
        os << " ";
}

void pretty::ASTPrinter::printAST(llvm::raw_ostream& os, sema::Sema& sema) {
    printErrorList(os, sema.TheErrorList);
    NEXTLINE;
    printSymbolTable(os, sema.TheASTContext->Symtbl);
    NEXTLINE;
    printClassList(os, sema.TheASTContext->Classes);
    NEXTLINE;
}

void pretty::ASTPrinter::printErrorList(llvm::raw_ostream& os, sema::ErrorList& errorlist) {
    INDENT; os << "ErrorList:"; NEXTLINE;
    INCINDENT;
    for (auto& e : errorlist) {
        INDENT; os << e; NEXTLINE;
    }
    DECINDENT;
}

void pretty::ASTPrinter::printSymbolTable(llvm::raw_ostream& os, ast::SymbolTable& TheSymbolTable) {
    INDENT; os << "Symbol Table:"; NEXTLINE;
    INCINDENT;
    INDENT; os << "TODO"; NEXTLINE;
    DECINDENT;
}

void pretty::ASTPrinter::printClassList(llvm::raw_ostream& os, ast::ClassList& TheClassList) {
    INDENT; os << "ClassList:"; NEXTLINE;
    INCINDENT;
    for (auto& c : TheClassList) {
        if (!IsPrintBuiltin 
            && ( c.Annotation->TheClassKind != sema::ClassAnnotation::CK_Trivial )) continue;
        printClass(os, c);
    }
    DECINDENT;
}

void pretty::ASTPrinter::printClass(llvm::raw_ostream& os, ast::Class& TheClass) {
    INDENT; os << "class " << TheClass.Name.getName() << " inherits " << TheClass.Inheirt.getName(); NEXTLINE;
    INCINDENT;
    auto& annot = TheClass.Annotation;
    INDENT; os << ANNOT(annot) << "InheritDepth=" << annot->InheritDepth << "; " 
        << "InitLocalVarN=" << TheClass.Annotation->InitLocalVarN; NEXTLINE;
    INDENT; printScope(os, &TheClass.Annotation->Scope); NEXTLINE;
    for(auto& a : TheClass.Attrs) {
        printAttr(os, a);
    }
    for(auto& m : TheClass.Methods) {
        printMethod(os, m);
    }
    DECINDENT;
}

void pretty::ASTPrinter::printAttr(llvm::raw_ostream& os, ast::AttrFeature& attr) {
    INDENT; os << "attr " << FORMAL(attr.Formal); NEXTLINE;
    INCINDENT;
    {
        INDENT; os << ANNOT(attr.Annotation) << "attrOffset=" << attr.Annotation->AttrOffset << "; "; NEXTLINE;
        if (attr.Init.has_value()) {
            INDENT; os << "attrInit <- {"; NEXTLINE;
            INCINDENT;
            printExpr(os, attr.Init.value());
            DECINDENT;
            INDENT; os << "}"; NEXTLINE;
        }
    }
    DECINDENT;
}

void pretty::ASTPrinter::printMethod(llvm::raw_ostream& os, ast::MethodFeature& method) {
    INDENT; os << "method " << method.Name.getName() << " (";
    for(auto& p : method.FormalParams) {
        os << FORMAL(p) << ", ";
    }
    os << ") : " << method.RetType.getName(); NEXTLINE;
    INCINDENT;
    {
        INDENT; os << ANNOT(method.Annotation) << "methodOff=" << method.Annotation->MethodOffset << "; " 
            << "LocalVarN=" << method.Annotation->BodyLocalVarN; NEXTLINE;
        INDENT; printScope(os, &method.Annotation->MethodScope); NEXTLINE;

        INDENT; os << "methodBody{"; NEXTLINE;
        INCINDENT;
        printExpr(os, method.Body);
        DECINDENT;
        INDENT; os << "}"; NEXTLINE;
    }
    DECINDENT;
}

void pretty::ASTPrinter::printScope(llvm::raw_ostream& os, sema::SemaScope* scope) {
    os << "Scope: total:" << scope->getLocalVarN() << "; ";
    for(auto& ent : *scope) {
        os << std::get<1>(ent.second) << ":" << ent.first.getName() << "; ";
    }
}

namespace {

#undef INDENT
#define INDENT Printer.printIndent(os)
#undef INCINDENT
#define INCINDENT ++Printer.Indent
#undef DECINDENT
#define DECINDENT --Printer.Indent
#define SUBEXPR(e) INCINDENT; e.accept(*this); DECINDENT

class PrintExprVisitor : public ast::ExprVisitor {
public:
    llvm::raw_ostream& os;
    pretty::ASTPrinter& Printer;
    PrintExprVisitor(llvm::raw_ostream& theOs, pretty::ASTPrinter& printer)
        : os(theOs), Printer(printer) {}

public:
void operator()(ast::Expr &expr, ast::ExprInt &rawExpr) {
    INDENT; os << "Int:" << rawExpr.Val; NEXTLINE;
}

void operator()(ast::Expr &expr, ast::ExprFloat &rawExpr) {
    INDENT; os << "Float:" << rawExpr.Val; NEXTLINE;
}

void operator()(ast::Expr &expr, ast::ExprBool &rawExpr) {
    INDENT; os << "Bool:" << rawExpr.Val; NEXTLINE;
}

void operator()(ast::Expr &expr, ast::ExprString &rawExpr) {
    INDENT; os << "String:" << rawExpr.Val; NEXTLINE;
}

void operator()(ast::Expr &expr, ast::ExprSymbol &rawExpr) {
    INDENT; os << "Symbol:" << rawExpr.TheSymbol.getName(); NEXTLINE;
}

void operator()(ast::Expr &expr, ast::ExprAssign &rawExpr) {
    INDENT; os << rawExpr.Variable.getName() << " <-"; NEXTLINE;
    SUBEXPR(rawExpr.Value);
}

void operator()(ast::Expr &expr, ast::ExprDispatch &rawExpr) {
    INDENT; os << "dispatch expr:" ; NEXTLINE;
    INDENT; os << "callee="; NEXTLINE;
    SUBEXPR(rawExpr.Callee);
    INDENT; os << "method=" << rawExpr.Method.getName(); NEXTLINE;
    INDENT; os << "args="; NEXTLINE;
    for(auto& arg : rawExpr.Args) {
        SUBEXPR(arg);
    }
}

void operator()(ast::Expr &expr, ast::ExprStaticDispatch &rawExpr) {
    INDENT; os << "static dispatch expr:" ; NEXTLINE;
    INDENT; os << "callee="; NEXTLINE;
    SUBEXPR(rawExpr.Callee);
    INDENT; os << "type=" << rawExpr.Type.getName(); NEXTLINE;
    INDENT; os << "method=" << rawExpr.Method.getName(); NEXTLINE;
    INDENT; os << "args="; NEXTLINE;
    for(auto& arg : rawExpr.Args) {
        SUBEXPR(arg);
    }
}

void operator()(ast::Expr &expr, ast::ExprCond &rawExpr) {
    INDENT; os << "if"; NEXTLINE;
    SUBEXPR(rawExpr.Cond);
    INDENT; os << "then"; NEXTLINE;
    SUBEXPR(rawExpr.ThenBranch);
    INDENT; os << "else"; NEXTLINE;
    SUBEXPR(rawExpr.ElseBranch);
    INDENT; os << "fi"; NEXTLINE;
}

void operator()(ast::Expr &expr, ast::ExprLoop &rawExpr) {
    INDENT; os << "while"; NEXTLINE;
    SUBEXPR(rawExpr.Cond);
    INDENT; os << "loop"; NEXTLINE;
    SUBEXPR(rawExpr.LoopBody);
    INDENT; os << "pool"; NEXTLINE;
}

void operator()(ast::Expr &expr, ast::ExprCase &rawExpr) {
    auto annot = static_cast<sema::ExprCaseAnnotation*>(expr.Annotation);
    INDENT; os << "case"; NEXTLINE;
    INDENT; os << ANNOT(annot) << "totalLocalVar=" << annot->BranchScope[0].getLocalVarN(); NEXTLINE;
    SUBEXPR(rawExpr.Cond);
    INDENT; os << "of"; NEXTLINE;
    for(auto& branch : rawExpr.Branchs) {
        INDENT; os << FORMAL(branch.Formal) << " =>"; NEXTLINE;
        SUBEXPR(branch.Body);
    }
    INDENT; os << "esac"; NEXTLINE;
}

void operator()(ast::Expr &expr, ast::ExprBlock &rawExpr) {
    INDENT; os << "block{"; NEXTLINE;
    for(auto& e : rawExpr.Exprs) {
        SUBEXPR(e);
    }
    INDENT; os << "}"; NEXTLINE;
}

void operator()(ast::Expr &expr, ast::ExprLet &rawExpr) {
    auto annot = static_cast<sema::ExprLetAnnotation*>(expr.Annotation);
    INDENT; os << "let"; NEXTLINE;
    INDENT; os << ANNOT(annot); NEXTLINE;
    INDENT; Printer.printScope(os, &annot->LocalScope); NEXTLINE;
    INCINDENT;
    for(auto& init : rawExpr.InitVariables) {
        INDENT; os << FORMAL(init.Formal);
        if (init.Init.has_value()) {
            os << " <-"; NEXTLINE;
            SUBEXPR(init.Init.value());
        } else {
            NEXTLINE;
        }
    }
    DECINDENT;
    INDENT; os << "in"; NEXTLINE;
    SUBEXPR(rawExpr.LetBody);
}

void operator()(ast::Expr &expr, ast::ExprNew &rawExpr) {
    INDENT; os << "new " << rawExpr.Type.getName(); NEXTLINE;
}

void operator()(ast::Expr &expr, ast::ExprSelf &rawExpr) {
    INDENT; os << "self"; NEXTLINE;
}

void operator()(ast::Expr &expr, ast::ExprNull &rawExpr) {
    INDENT; os << "null"; NEXTLINE;
}

void operator()(ast::Expr &expr, ast::ExprArithB &rawExpr) {
    INDENT; os << "binaryOperator= " << ast::ExprArithB::OperatorLiteral[rawExpr.Operator]; NEXTLINE;
    INDENT; os << "leftOperand="; NEXTLINE;
    SUBEXPR(rawExpr.Left);
    INDENT; os << "rightOperand="; NEXTLINE;
    SUBEXPR(rawExpr.Right);
}

void operator()(ast::Expr &expr, ast::ExprArithU &rawExpr) {
    INDENT; os << "binaryOperator= " << ast::ExprArithU::OperatorLiteral[rawExpr.Operator]; NEXTLINE;
    INDENT; os << "operand="; NEXTLINE;
    SUBEXPR(rawExpr.Operand);
}
};

}

void pretty::ASTPrinter::printExpr(llvm::raw_ostream& os, ast::Expr& expr) {
    auto visitor = PrintExprVisitor(os, *this);
    expr.accept(visitor);
}

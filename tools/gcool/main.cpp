#include <iostream>
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/ADT/STLExtras.h"
#include "gcool/AST/Expr.h"
#include "gcool/AST/AST.h"
#include "gcool/Parser/Parser.h"
#include "gcool/Lexer/Lexer.h"

using namespace gcool;
using namespace gcool::ast;

void TestHelper(const char* input, ast::ASTContext& context, ast::ClassList& expect) {
    yyscan_t scanner;
    yylex_init(&scanner);
    yy_scan_string(input, scanner);
    Parser parser{scanner, &context};
    parser.parse();
    llvm::outs() << (expect == context.Classes);
}

void test() {
    ast::ASTContext context;
    const char* input = 
    R"(
        class Main
        {

        };
        class help_class{ };
    )";

    ast::ClassList expect{
        Class{ context.Symtbl.get("Main"), context.Symtbl.getObject() },
        Class{ context.Symtbl.get("help_class"), context.Symtbl.getObject() }
    };
    TestHelper(input, context, expect);
}

int main(int argc, char** argv) 
{
    llvm::LLVMContext TheContext;
    llvm::IRBuilder<> TheBuilder(TheContext);
    llvm::Module TheModule("Main", TheContext);

    auto v1 = llvm::ConstantInt::get(TheContext, llvm::APInt(32, 10));
    auto v2 = llvm::ConstantInt::get(TheContext, llvm::APInt(32, 20));
    auto add1 = TheBuilder.CreateAdd(v1, v2, "add");

    auto intTy = llvm::Type::getInt32Ty(TheContext);

    {
        auto FT1 = llvm::FunctionType::get(intTy, {}, false);
        llvm::Function::Create(FT1, llvm::Function::ExternalLinkage, "main", TheModule);
        auto FT2 = llvm::FunctionType::get(intTy, {intTy, intTy}, false);
        llvm::Function::Create(FT2, llvm::Function::ExternalLinkage, "iftest", TheModule);
    }
    
    // main function
    {   
        auto TheFunction = TheModule.getFunction("main");
        auto BB = llvm::BasicBlock::Create(TheContext, "entry", TheFunction);
        TheBuilder.SetInsertPoint(BB);
        auto v3 = TheBuilder.CreateCall(TheModule.getFunction("iftest"), {v1, v2});
        TheBuilder.CreateRet(v3);
    }

    // ifTest min function
    {
        auto TheFunction = TheModule.getFunction("iftest");
        auto BBEntry = llvm::BasicBlock::Create(TheContext, "entry", TheFunction);
        // or: TheFunction->getBasicBlockList().push_back(BB);
        auto BBThen = llvm::BasicBlock::Create(TheContext, "then", TheFunction);
        auto BBElse = llvm::BasicBlock::Create(TheContext, "else", TheFunction);
        auto BBMerge = llvm::BasicBlock::Create(TheContext, "merge", TheFunction);

        auto arg1 = TheFunction->getArg(0);
        auto arg2 = TheFunction->getArg(1);
        TheBuilder.SetInsertPoint(BBEntry);
        auto cond = TheBuilder.CreateICmpSLT(arg1, arg2, "ifcond");
        TheBuilder.CreateCondBr(cond, BBThen, BBElse);
        
        TheBuilder.SetInsertPoint(BBThen);
        auto thenV = arg1;
        TheBuilder.CreateBr(BBMerge);
        
        TheBuilder.SetInsertPoint(BBElse);
        auto elseV = arg2;
        TheBuilder.CreateBr(BBMerge);
        
        TheBuilder.SetInsertPoint(BBMerge);
        auto phi = TheBuilder.CreatePHI(intTy, 2, "ifphi");
        phi->addIncoming(thenV, BBThen);
        phi->addIncoming(elseV, BBElse);
        
        TheBuilder.CreateRet(phi);
        
    }
    auto context = ASTContext{};

    ExprList l1{context.ExprAlloc.allocExpr(new ExprInt{1})};
    ExprList l2{context.ExprAlloc.allocExpr(new ExprInt{1})};
    l2 = l1;
    

    TheModule.print(llvm::outs(), nullptr);
}
#include <unordered_map>
#include <vector>
#include <string_view>
#include "gcool/LLVMIRGen/LLVMIRGen.h"
#include "gcool/AST/Expr.h"

using namespace gcool;

#define ASTCONTEXT TheSema->TheASTContext

ir::LLVMIRGen::LLVMIRGen(sema::Sema* sema)
    : Context()
    , Module("Main", Context)
    , IRBuilder(Context)
    , BuiltIntTy(llvm::Type::getInt64Ty(Context))
    , BuiltFloatTy(llvm::Type::getDoubleTy(Context))
    , BuiltBoolTy(llvm::Type::getInt1Ty(Context))
    , VTableSlotTy(llvm::FunctionType::get(llvm::Type::getInt32Ty(Context), true)->getPointerTo())
    , VTableTy(VTableSlotTy->getPointerTo())
    , FatPointer(llvm::StructType::create(Context, "FatPointer"))
    , TheSema(sema)
{
    FatPointer->setBody({VTableTy, FatPointer->getPointerTo()}, true);
    // new llvm::GlobalVariable(
    //     Module, FatPointer, true, 
    //     llvm::GlobalValue::ExternalLinkage,
    //     llvm::UndefValue::get(FatPointer),
    //     "test");
}

ir::LLVMIRGen::~LLVMIRGen() = default;

bool ir::LLVMIRGen::emitLLVMIR() {
    if (TheSema->TheErrorList.size() != 0) {
        return false;
    }
    pass1();
    pass2();
    pass3();
    return true;
}

void ir::LLVMIRGen::pass1() {
    this->emitRuntime(); // GCoolRuntimeIR.cpp
}

void ir::LLVMIRGen::pass2() {
    for(auto& c : ASTCONTEXT->Classes) {
        if (c.Annotation->IsBuiltin) continue;
        emitClassDecl(c);
    }
}

void ir::LLVMIRGen::emitClassDecl(ast::Class& c) {

}

void ir::LLVMIRGen::pass3() {

}

void ir::LLVMIRGen::emitClassDefination(ast::Class& c) {

}

void ir::LLVMIRGen::addStructT(llvm::StructType* s) {
    TheStructTypeMap.insert({s->getName(), s});
}

llvm::StructType* ir::LLVMIRGen::getStructT(std::string_view s) {
    auto p = TheStructTypeMap.find(s);
    assert(p != TheStructTypeMap.end() && "struct get before declaration");
    return p->second;
}

void ir::LLVMIRGen::print(llvm::raw_ostream& os) {
    Module.print(os, nullptr);
}

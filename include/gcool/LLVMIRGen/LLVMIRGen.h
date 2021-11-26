#pragma once
#include <memory>
#include <string_view>
#include "gcool/AST/AST.h"
#include "gcool/Sema/Sema.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Module.h"

namespace llvm {
class raw_ostream;
}

namespace gcool {
namespace ir {

using StructTypeMap = std::unordered_map<std::string_view, llvm::StructType*>;
using TypeList = std::vector<llvm::Type*>;

class LLVMIRGen {
private:
    llvm::LLVMContext       Context;
    llvm::Module            Module;
    llvm::IRBuilder<>       IRBuilder;
    llvm::IntegerType*      BuiltIntTy;
    llvm::Type*             BuiltFloatTy;
    llvm::IntegerType*      BuiltBoolTy;
    llvm::PointerType*      VTableSlotTy;
    llvm::PointerType*      VTableTy;
    llvm::StructType*       FatPointer;
    StructTypeMap           TheStructTypeMap;
    sema::Sema*             TheSema;
public:
    LLVMIRGen(sema::Sema* sema);
    ~LLVMIRGen();
    bool emitLLVMIR();
private:
    // emitBuitin
    void pass1();
    void emitRuntime();
    // emitDecl
    void pass2();
    void emitClassDecl(ast::Class& c);
    // emitExpr
    void pass3();
    void emitClassDefination(ast::Class& c);
    // helper function
    void addStructT(llvm::StructType* s);
    llvm::StructType* getStructT(std::string_view s);
public:
    void print(llvm::raw_ostream& os);
};

}
}
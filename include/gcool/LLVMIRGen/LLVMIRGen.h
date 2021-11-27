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

using StructTypeMap = std::unordered_map<ast::Symbol, llvm::StructType*>;
using GlobalVariableMap = std::unordered_map<ast::Symbol, llvm::GlobalVariable*>;
using StringBufList = std::vector<const char*>;
using TypeList = std::vector<llvm::Type*>;
using ConstantList = std::vector<llvm::Constant*>;

class LLVMIRGen {
private:
    llvm::LLVMContext       Context;
    llvm::Module            Module;
    llvm::IRBuilder<>       IRBuilder;
    llvm::Type*             BuiltObjHold;
    llvm::IntegerType*      BuiltIntTy;
    llvm::Type*             BuiltFloatTy;
    llvm::IntegerType*      BuiltBoolTy;
    llvm::StructType*       ClassInfoTy;
    int                     ClassInfoSize; // N pointer
    llvm::PointerType*      VMethodSlotTy;
    llvm::StructType*       VTableTy;
    llvm::PointerType*      VTableRefTy;
    StructTypeMap           FatPointerTyMap;
    StructTypeMap           ObejctTyMap;
    GlobalVariableMap       VTableMap;
    sema::Sema*             TheSema;

    StringBufList           NameBufList;
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
    // emitExpr
    void pass3();

    // helper function
    std::string_view bufName(std::string_view lhs, std::string_view rhs);
    llvm::StructType* addFatPointer(ast::Symbol className);
    llvm::StructType* getFatPointer(ast::Symbol className);
    llvm::StructType* addObjectStruct(ast::Symbol className);
    llvm::StructType* getObjectStruct(ast::Symbol className);
    llvm::GlobalVariable* addVTable(ast::Symbol className, int vMethodN);
    void initVTable(ast::Class& c, llvm::ArrayRef<llvm::Constant*> methodInit);
    llvm::GlobalVariable* getVTable(ast::Symbol className);
public:
    void print(llvm::raw_ostream& os);
};

}
}
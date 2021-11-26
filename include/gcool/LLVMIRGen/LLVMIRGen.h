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
using ConstantMap = std::unordered_map<std::string_view, llvm::Constant*>;
using StringBufList = std::vector<const char*>;
using FunctionList = std::vector<llvm::Function*>;
using TypeList = std::vector<llvm::Type*>;

class LLVMIRGen {
private:
    llvm::LLVMContext       Context;
    llvm::Module            Module;
    llvm::IRBuilder<>       IRBuilder;
    llvm::Type*             BuiltObjHold;
    llvm::IntegerType*      BuiltIntTy;
    llvm::Type*             BuiltFloatTy;
    llvm::IntegerType*      BuiltBoolTy;
    llvm::PointerType*      VTableSlotTy;
    llvm::PointerType*      VTableTy;
    StructTypeMap           FatPointerTyMap;
    StructTypeMap           ObejctTyMap;
    ConstantMap             VTableMap;
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
    llvm::StructType* addFatPointer(std::string_view className);
    llvm::StructType* getFatPointer(std::string_view className);
    llvm::StructType* addObjectStruct(std::string_view className);
    llvm::StructType* getObjectStruct(std::string_view className);
    llvm::Constant* addVTable(std::string_view className, llvm::ArrayRef<llvm::Constant*> init);
    llvm::Constant* getVTable(std::string_view className);
public:
    void print(llvm::raw_ostream& os);
};

}
}
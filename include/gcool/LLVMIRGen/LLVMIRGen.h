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

class ExprIRGenVisitor;

using StructTypeMap = std::unordered_map<ast::Symbol, llvm::StructType*>;
using GlobalVariableMap = std::unordered_map<ast::Symbol, llvm::GlobalVariable*>;
using StringBufList = std::vector<const char*>;
using TypeList = std::vector<llvm::Type*>;
using ConstantList = std::vector<llvm::Constant*>;

class LLVMIRGen {
    friend class ExprIRGenVisitor;
private:
    llvm::LLVMContext       Context;
    llvm::Module            Module;
    llvm::IRBuilder<>       IRBuilder;
    llvm::Type*             BuiltObjHold;
    llvm::IntegerType*      BuiltIntTy;
    llvm::Type*             BuiltFloatTy;
    llvm::IntegerType*      BuiltBoolTy;
    llvm::StructType*       ClassInfoTy;
    llvm::PointerType*      VMethodSlotTy;
    llvm::StructType*       VTableTy;
    llvm::PointerType*      VTableRefTy;
    llvm::PointerType*      ObjectRefTy;
    StructTypeMap           FatPointerTyMap;
    StructTypeMap           ObejctTyMap;
    GlobalVariableMap       VTableMap;
    sema::Sema*             TheSema;

    std::string             TempStringBuf;
public:
    LLVMIRGen(sema::Sema* sema);
    ~LLVMIRGen();
    bool emitLLVMIR();
private:
    // Declare FatPointer for allClass
    void pass1();

    // Define ObejctStruct
    // Define VTable
    // Declare Method
    void pass2();
    
    // Define Method, emit Expr IR
    void pass3();
    void emitNative();
    void emitNewMethod(ast::Class* c);
    void emitMethod(ast::Class* c, ast::MethodFeature* m);
    llvm::Value* emitExpr(ast::Expr expr);

    // helper function
    llvm::StructType* addFatPointer(ast::Symbol className);
    llvm::StructType* getFatPointer(ast::Symbol className);
    llvm::StructType* addObjectStruct(ast::Symbol className);
    llvm::StructType* getObjectStruct(ast::Symbol className);
    llvm::GlobalVariable* addVTable(ast::Symbol className, ast::Class* classInfo, llvm::ArrayRef<llvm::Constant*> methodInit);
    llvm::GlobalVariable* getVTable(ast::Symbol className);
    llvm::Constant* getVTableConstant(ast::Symbol className);
    llvm::Function* addMethod(llvm::FunctionType* ft, ast::Symbol classNameS, ast::Symbol methodNameS);
    llvm::Function* getMethod(ast::Symbol classNameS, ast::Symbol methodNameS);
    enum BuiltinFunctionKind {
        BK_Malloc,
    };
    llvm::Function* getBuiltinFunction(BuiltinFunctionKind Bk);
public:
    void print(llvm::raw_ostream& os);
};

}
}
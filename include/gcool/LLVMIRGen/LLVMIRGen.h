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

using GlobalVariableMap = std::unordered_map<ast::Symbol, llvm::GlobalVariable*>;
using ConstantList = std::vector<llvm::Constant*>;
using TypeList = std::vector<llvm::Type*>;
using ValueList = std::vector<llvm::Value*>;

class LLVMIRGen {
    friend class ExprIRGenVisitor;
private:
    llvm::LLVMContext       Context;
    llvm::Module            Module;
    llvm::IRBuilder<>       IRBuilder;
    llvm::Type*             Holder64bit;
    llvm::IntegerType*      BuiltIntTy;
    llvm::Type*             BuiltFloatTy;
    llvm::IntegerType*      BuiltBoolTy;
    llvm::StructType*       FatPointerTy;
    llvm::StructType*       ClassInfoTy;
    llvm::PointerType*      VMethodSlotTy;
    llvm::StructType*       VTableTy;
    llvm::PointerType*      VTableRefTy;
    llvm::ArrayType*        ObjectStructTy;
    llvm::PointerType*      ObjectRefTy;
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
    void emitDeriver();
    llvm::Value* emitExpr(ast::Expr expr);

    // helper function
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
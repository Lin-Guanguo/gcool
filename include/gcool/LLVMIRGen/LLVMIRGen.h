#pragma once
#include <memory>
#include "gcool/AST/AST.h"
#include "gcool/Sema/Sema.h"

namespace llvm {
class LLVMContext;
class Module;
template <typename FolderTy,
          typename InserterTy>
class IRBuilder;
class raw_ostream;
}

namespace gcool {
namespace ir {
class LLVMIRGen {
public:
    std::unique_ptr<llvm::LLVMContext> Context;
    std::unique_ptr<llvm::Module> Module;
    std::unique_ptr<llvm::IRBuilder<>> IRBuilder;
    sema::Sema* TheSema;
public:
    LLVMIRGen(sema::Sema* sema) : TheSema(sema) {}
    void genLLVMIR();
    void print(llvm::raw_ostream& os);
};

}
}
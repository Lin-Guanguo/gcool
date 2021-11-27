add_gcool_library(LLVMIRGen
    LLVMIRGen.cpp
    NativeIRGen.cpp
    ExprIRGen.cpp
)

target_include_directories(LLVMIRGen
    PUBLIC
    ${GCOOL_INCLUDE_DIR}
)

target_link_llvm_public(LLVMIRGen core)

target_link_libraries(LLVMIRGen
    PUBLIC
    AST
    Sema
)
add_gcool_library(IRGen
    IRGen.cpp
)

target_include_directories(IRGen
    PUBLIC
    ${GCOOL_INCLUDE_DIR}
)

target_link_llvm(AST support)

target_link_libraries(IRGen
    PUBLIC
    AST
    Sema
)
add_gcool_library(AST
    AST.cpp
    Expr.cpp
    Symbol.cpp
)

target_include_directories(AST
    PUBLIC
    ${GCOOL_INCLUDE_DIR}
)

target_link_llvm(AST support)

target_compile_features(AST
    PUBLIC
    cxx_std_20
)
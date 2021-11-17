add_gcool_library(Basic
    Diag.cpp
)

target_include_directories(Basic
    PUBLIC
    ${GCOOL_INCLUDE_DIR}
)

target_link_llvm(Basic support core)
add_gcool_example(IRApiExample
    IRApiExample.cpp
    )

target_include_directories(IRApiExample
    PUBLIC
    ${GCOOL_INCLUDE_DIR}
    )

target_link_llvm(IRApiExample core)
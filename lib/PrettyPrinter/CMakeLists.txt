add_gcool_library(PrettyPrinter
    ASTPrinter.cpp
)

target_include_directories(PrettyPrinter
    PUBLIC
    ${GCOOL_INCLUDE_DIR}
)

target_link_libraries(PrettyPrinter
    PUBLIC
    AST
    Sema
)
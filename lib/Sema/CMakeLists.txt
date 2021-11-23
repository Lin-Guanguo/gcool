add_gcool_library(Sema
    Sema.cpp
    Annotation.cpp
    ASTPrinter.cpp
)

target_include_directories(Sema
    PUBLIC
    ${GCOOL_INCLUDE_DIR}
)

target_link_libraries(Sema
    PUBLIC
    AST
    Basic
)
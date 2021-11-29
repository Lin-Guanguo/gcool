add_executable(SemaTest
SemaTest.cpp
    )

target_link_llvm(SemaTest support)

target_link_libraries(SemaTest
    PRIVATE
    GTestLib
    Parser
    Lexer
    AST
    Sema
    PrettyPrinter
    )
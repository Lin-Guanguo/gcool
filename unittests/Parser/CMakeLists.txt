add_executable(ParserTest
    ParserTest.cpp
    )

target_link_libraries(ParserTest
    PRIVATE
    GTestLib
    Lexer
    Parser
    AST
    )
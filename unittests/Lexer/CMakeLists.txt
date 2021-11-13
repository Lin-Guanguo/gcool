add_executable(LexerTest
    LexerTest.cpp
    )

target_link_libraries(LexerTest
    PRIVATE
    GTestLib
    Lexer
    )
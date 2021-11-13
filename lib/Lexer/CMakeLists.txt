add_gcool_library(Lexer
    Lexer.cpp
    )

target_include_directories(Lexer
    PUBLIC
    ${GCOOL_INCLUDE_DIR}
    ${GCOOL_INCLUDE_DIR}/gcool/Lexer
    )

target_link_libraries(Lexer
    PUBLIC
    Parser
    )
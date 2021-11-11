add_gcool_library(Parser
    Parser.cpp
    )

target_include_directories(Parser
    PUBLIC
    ${GCOOL_INCLUDE_DIR}/gcool/Parser
    )
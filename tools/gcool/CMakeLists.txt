add_gcool_tool(gcool
    driver.cpp
    )

target_link_llvm(gcool core)

target_link_libraries(gcool
    PRIVATE
    Basic
    Lexer
    Parser
    AST
    Sema
    PrettyPrinter
    LLVMIRGen
    )
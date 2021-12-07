add_gcool_tool(driver
    driver.cpp
    )

target_link_llvm(driver core)

target_link_libraries(driver
    PRIVATE
    Basic
    Lexer
    Parser
    AST
    Sema
    PrettyPrinter
    LLVMIRGen
    )
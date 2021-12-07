add_gcool_tool(gcooltest
    main.cpp
    )

target_link_llvm(gcooltest support)

target_link_libraries(gcooltest
    PRIVATE
    Basic
    AST
    Parser
    Lexer
    Sema
    PrettyPrinter
    LLVMIRGen
    )
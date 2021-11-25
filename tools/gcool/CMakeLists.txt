add_gcool_tool(gcool
    main.cpp
    )

target_link_llvm(gcool support)

target_link_libraries(gcool
    PRIVATE
    Basic
    AST
    Parser
    Lexer
    Sema
    PrettyPrinter
    LLVMIRGen
    )
set(LLVM_LINK_COMPONENTS
    Support
    Core
    )

add_gcool_tool(gcool
    main.cpp
    )

target_include_directories(gcool
PUBLIC
    ${LLVM_INCLUDE_DIRS}
    )
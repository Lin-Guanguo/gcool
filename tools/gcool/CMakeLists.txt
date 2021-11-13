add_gcool_tool(gcool
    main.cpp
    )

llvm_map_components_to_libnames(llvm_libs support core)

target_link_libraries(gcool
    PUBLIC
    LLVMLib
    ${llvm_libs}
    )
macro(add_gcool_library name)
    if(BUILD_SHARED_LIBS)
        set(LIBTYPE SHARED)
    else()
        set(LIBTYPE STATIC)
    endif()
    add_library(${name} ${LIBTYPE} ${ARGN})
    target_link_libraries(${name} PUBLIC ${LLVM_COMMON_LIBS})
endmacro()

macro(add_gcool_executable name)
    add_executable(${name} ${ARGN} )
endmacro()

macro(add_gcool_tool name)
    add_gcool_executable(${name} ${ARGN})
endmacro()

macro(target_link_llvm name)
    llvm_map_components_to_libnames(llvm_libs ${ARGN})
    target_link_libraries(${name}
        PRIVATE
        ${llvm_libs}
        )
    target_include_directories(${name}
        PRIVATE
        ${LLVM_INCLUDE_DIRS}
        )
endmacro(target_link_llvm)


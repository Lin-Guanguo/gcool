cmake_minimum_required(VERSION 3.13.4)

if(GCOOL_SOURCE_DIR STREQUAL GCOOL_BINARY_DIR)
    message(FATAL_ERROR "In-source builds are not allowed. ")
endif()

project(GCOOL)
add_compile_options("-Wall")

find_package(LLVM REQUIRED CONFIG)
message(STATUS "Using LLVM version ${LLVM_VERSION}")

set(GCOOL_INCLUDE_DIR "${GCOOL_SOURCE_DIR}/include" 
    CACHE FILEPATH "include dir")

option(BUILD_SHARED_LIBS "Build shared libraries." OFF)

list(APPEND CMAKE_MODULE_PATH ${LLVM_CMAKE_DIR})
list(APPEND CMAKE_MODULE_PATH "${GCOOL_SOURCE_DIR}/cmake/modules")
include(AddLLVM)
include(AddGCool)

add_subdirectory(lib)
add_subdirectory(tools)
add_subdirectory(unittests)
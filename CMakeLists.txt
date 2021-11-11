cmake_minimum_required(VERSION 3.13.4)

if(GCOOL_SOURCE_DIR STREQUAL GCOOL_BINARY_DIR)
    message(FATAL_ERROR "In-source builds are not allowed. ")
endif()

project(GCOOL)

find_package(LLVM REQUIRED CONFIG)
message(STATUS "Using LLVM version ${LLVM_VERSION}")

set(CACHE GCOOL_INCLUDE_DIRS "${GCOOL_SOURCE_DIR}/include")
set(CACHE GCOOL_INCLUDE_GEN_DIRS "${GCOOL_BINARY_DIR}/include")

list(APPEND CMAKE_MODULE_PATH ${LLVM_CMAKE_DIR})
list(APPEND CMAKE_MODULE_PATH "${GCOOL_SOURCE_DIR}/cmake/modules")
include(AddLLVM)
include(AddGCool)

add_subdirectory(lib)
add_subdirectory(tools)
add_subdirectory(unittests)
cmake_minimum_required(VERSION 3.13.4)

if(GCOOL_SOURCE_DIR STREQUAL GCOOL_BINARY_DIR)
    message(FATAL_ERROR "In-source builds are not allowed. ")
endif()

project(GCOOL)
add_compile_options("-Wall")

option(BUILD_SHARED_LIBS "Build shared libraries." OFF)
set(GCOOL_INCLUDE_DIR "${GCOOL_SOURCE_DIR}/include")

find_package(LLVM REQUIRED CONFIG)
message(STATUS "Using LLVM version ${LLVM_VERSION}")
message(STATUS "LLVM_INCLUDE_DIRS ${LLVM_INCLUDE_DIRS}")
message(STATUS "LLVM_LIBRARY_DIRS ${LLVM_LIBRARY_DIRS}")
list(APPEND CMAKE_MODULE_PATH ${LLVM_CMAKE_DIR})
list(APPEND CMAKE_MODULE_PATH "${GCOOL_SOURCE_DIR}/cmake/modules")
include(AddLLVM)
include(AddGCool)


# Google Test, test target link to this target
add_library(GTestLib INTERFACE)
set(GTEST_DIR "/usr/local/gtest" 
    CACHE FILEPATH "google test dir")
target_include_directories(GTestLib
    INTERFACE
    "${GTEST_DIR}/include"
    )
target_link_libraries(GTestLib
    INTERFACE
    "${GTEST_DIR}/lib/libgtest.a" 
    "${GTEST_DIR}/lib/libgtest_main.a" 
    pthread
    )

add_subdirectory(lib)
add_subdirectory(tools)
add_subdirectory(unittests)
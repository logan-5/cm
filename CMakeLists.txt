cmake_minimum_required(VERSION 3.1.0)
project(cm VERSION 0.1.0)

option(CM_BUILD_TESTS "build tests" OFF)
if(${CM_BUILD_TESTS})
    enable_testing()
    add_subdirectory(test)
endif()

add_library(cm INTERFACE)
target_include_directories(cm INTERFACE include/)
add_compile_definitions(CM_ENABLE_ASSERTIONS=${CM_ENABLE_ASSERTIONS})

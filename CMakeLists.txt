cmake_minimum_required(VERSION 3.1.0)
project(cm VERSION 0.1.0)

enable_testing()
add_subdirectory(test)

add_library(cm INTERFACE)
target_include_directories(cm INTERFACE include/)

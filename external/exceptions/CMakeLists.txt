cmake_minimum_required(VERSION 3.10)
project(exceptions)

add_library(exceptions STATIC exceptions.cpp)
target_include_directories(exceptions PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

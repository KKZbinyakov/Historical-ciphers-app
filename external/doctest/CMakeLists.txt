cmake_minimum_required(VERSION 3.10)
project(doctest)

add_library(doctest STATIC doctest.cpp)
target_include_directories(doctest PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

cmake_minimum_required(VERSION 3.10)
project(affine_ciphers)

add_library(affine_ciphers STATIC Affine_ciphers.cpp)
target_include_directories(affine_ciphers PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ../external/exceptions)

add_executable(affine_ciphers_tests Affine_ciphers_tests.cpp)
target_include_directories(affine_ciphers_tests PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ../external/doctest ../external/exceptions)
target_link_libraries(affine_ciphers_tests affine_ciphers doctest exceptions)

add_test(NAME AffineCiphersTest COMMAND affine_ciphers_tests)

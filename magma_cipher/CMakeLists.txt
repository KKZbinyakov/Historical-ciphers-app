cmake_minimum_required(VERSION 3.10)
project(magma_cipher)

add_library(magma_cipher STATIC magma_cipher.cpp)
target_include_directories(magma_cipher PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ../external/exceptions)

add_executable(magma_cipher_tests magma_tests.cpp)
target_include_directories(magma_cipher_tests PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ../external/doctest ../external/exceptions)
target_link_libraries(magma_cipher_tests magma_cipher doctest exceptions)

add_test(NAME MagmaCipherTest COMMAND magma_cipher_tests)

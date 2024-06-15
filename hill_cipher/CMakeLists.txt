cmake_minimum_required(VERSION 3.10)
project(hill_cipher)

add_library(hill_cipher STATIC Hill_encoder.cpp)
target_include_directories(hill_cipher PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ../external/exceptions)

add_executable(hill_cipher_tests Hill_encoder_tests.cpp)
target_include_directories(hill_cipher_tests PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ../external/doctest ../external/exceptions)
target_link_libraries(hill_cipher_tests hill_cipher doctest exceptions)

add_test(NAME HillCipherTest COMMAND hill_cipher_tests)

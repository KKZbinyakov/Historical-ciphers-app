cmake_minimum_required(VERSION 3.10)
project(vigenere_ciphers)

add_library(vigenere_ciphers STATIC vigenere_ciphers.cpp)
target_include_directories(vigenere_ciphers PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ../external/exceptions)

add_executable(vigenere_ciphers_tests vigenere_ciphers_tests.cpp)
target_include_directories(vigenere_ciphers_tests PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ../external/doctest ../external/exceptions)
target_link_libraries(vigenere_ciphers_tests vigenere_ciphers doctest exceptions)

add_test(NAME VigenereCiphersTest COMMAND vigenere_ciphers_tests)

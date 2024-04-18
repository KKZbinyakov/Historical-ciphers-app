cmake_minimum_required(VERSION 3.10.0)
add_executable(vigenere_ciphers_tests vigenere_ciphers_tests.cpp vigenere_ciphers.cpp)
target_link_libraries(vigenere_ciphers_tests PUBLIC doctest default)
add_test(NAME vigenere_ciphers_tests COMMAND vigenere_ciphers_tests --force-colors -d)


add_executable(vigenere_ciphers vigenere_ciphers.cpp main.cpp vigenere_ciphers.hpp)
target_link_libraries(vigenere_ciphers PUBLIC default)

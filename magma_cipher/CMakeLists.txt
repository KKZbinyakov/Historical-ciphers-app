cmake_minimum_required(VERSION 3.10.0)
add_executable(magma_tests magma_cipher.cpp magma_tests.cpp)
target_link_libraries(magma_tests PUBLIC doctest default)
add_test(NAME magma_tests COMMAND magma_tests --force-colors -d)

add_executable(magma_cipher magma_cipher.cpp main.cpp)
target_link_libraries(magma_cipher PUBLIC default)

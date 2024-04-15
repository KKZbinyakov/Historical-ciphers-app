cmake_minimum_required(VERSION 3.10.0)
add_executable(Affine_ciphers_tests Affine_ciphers.cpp Affine_ciphers_tests.cpp)
target_link_libraries(Affine_ciphers_tests PUBLIC doctest default)
add_test(NAME Affine_ciphers_tests COMMAND Affine_ciphers_tests --force-colors -d)

add_executable(Affine_ciphers Affine_ciphers.cpp main.cpp)
target_link_libraries(Affine_ciphers PUBLIC default)

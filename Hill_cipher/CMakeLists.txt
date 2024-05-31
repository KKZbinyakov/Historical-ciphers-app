cmake_minimum_required(VERSION 3.10.0)
add_executable(Hill_encoder_tests Hill_encoder_tests.cpp Hill_encoder.cpp)
target_link_libraries(Hill_encoder_tests PUBLIC doctest default)
add_test(NAME Hill_encoder_tests COMMAND Hill_encoder_tests —force-colors -d)


add_executable(Hill_encoder Hill_encoder.cpp main.cpp Hill_encoder.hpp)
target_link_libraries(Hill_encoder PUBLIC default)
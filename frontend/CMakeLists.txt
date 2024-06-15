cmake_minimum_required(VERSION 3.10)

project(Historical_ciphers_app)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 COMPONENTS Widgets REQUIRED)

add_executable(Historical_ciphers_app Historical_ciphers_app.cpp mainwindow.h Affine_ciphers.cpp Affine_ciphers.hpp vigenere_ciphers.cpp vigenere_ciphers.hpp Hill_encoder.cpp Hill_encoder.hpp magma_cipher.cpp magma_cipher.hpp exceptions.hpp)

target_link_libraries(Historical_ciphers_app Qt6::Widgets)

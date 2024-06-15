cmake_minimum_required(VERSION 3.10)
project(App)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")

# Enable testing
enable_testing()

# Add subdirectories
add_subdirectory(external/doctest)
add_subdirectory(external/exceptions)
add_subdirectory(affine_ciphers)
add_subdirectory(hill_cipher)
add_subdirectory(magma_cipher)
add_subdirectory(vigenere_ciphers)
add_subdirectory(frontend)


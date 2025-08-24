cmake_minimum_required(VERSION 3.16)
project(c_quantum_computer_simulation LANGUAGES C)

set(CMAKE_CXX_FLAGS "--std=c99")

enable_testing()

add_subdirectory(src)
add_subdirectory(test)
cmake_minimum_required(VERSION 3.22)
project(MathFunctions)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -fopenmp -O3")
set(CMAKE_C_STANDARD 99)

add_executable(math_app main.c)

add_library(math_functions math_functions.c)
target_link_libraries(math_app math_functions)

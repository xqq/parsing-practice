cmake_minimum_required(VERSION 3.2)
project(expr_calc)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(expr_calc ${SOURCE_FILES})
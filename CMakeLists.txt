cmake_minimum_required(VERSION 3.2)
project(parsing-practice)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Token.hpp Word.hpp Word.cpp Num.hpp Real.hpp Lexer.hpp Parser.hpp RPN.hpp)
add_executable(parsing-practice ${SOURCE_FILES})
cmake_minimum_required(VERSION 3.5.2)
project(test29)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lm")

set(SOURCE_FILES init.c emitter.c error.c lexer.c parser.c symbol.c main.c stack.c example.tab.c example.tab.h)
add_library(global.h stack.h)
add_executable(lab2komp ${SOURCE_FILES})
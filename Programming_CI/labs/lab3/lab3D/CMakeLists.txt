cmake_minimum_required(VERSION 3.5.2)
project(test29)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c99 -lm")

set(SOURCE_FILES symbol.c lab4b.tab.c lab4b.tab.h)
add_library(symtable.h)
add_executable(lab4b ${SOURCE_FILES})

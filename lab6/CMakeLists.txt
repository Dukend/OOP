cmake_minimum_required (VERSION 3.2)

project(prog)

set(CMAKE_CXX_STANDARD 17)

add_executable(prog lab6.cpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")


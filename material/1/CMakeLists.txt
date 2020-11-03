cmake_minimum_required(VERSION 3.5)

project(Examples_01)

add_executable(malloc malloc.cpp)
set_target_properties(malloc PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
        )

add_executable(square square.cpp)
set_target_properties(square PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
        )

add_executable(stackoverflow stackoverflow.cpp)
set_target_properties(stackoverflow PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
        )

add_executable(stream stream.cpp)
set_target_properties(stream PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
        )

add_executable(first_class first_class.cpp)
set_target_properties(first_class PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
        )

add_executable(second_class second_class.cpp)
set_target_properties(second_class PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
        )

add_executable(life life.cpp)
set_target_properties(life PROPERTIES
                CXX_STANDARD 14
                CXX_STANDARD_REQUIRED ON
                )
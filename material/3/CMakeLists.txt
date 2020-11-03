cmake_minimum_required(VERSION 3.5)

project(Examples_03)

add_executable(inheritance inheritance.cpp)
set_target_properties(inheritance PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
        )

add_executable(virtual virtual.cpp)
set_target_properties(virtual PROPERTIES
       CXX_STANDARD 14
       CXX_STANDARD_REQUIRED ON
       )

add_executable(multi_inheritance multi_inheritance.cpp)
set_target_properties(multi_inheritance PROPERTIES
       CXX_STANDARD 14
       CXX_STANDARD_REQUIRED ON
       )  

add_executable(cast cast.cpp)
set_target_properties(cast PROPERTIES
       CXX_STANDARD 14
       CXX_STANDARD_REQUIRED ON
       )  

add_executable(delete delete.cpp)
set_target_properties(delete PROPERTIES
       CXX_STANDARD 14
       CXX_STANDARD_REQUIRED ON
       )  

add_executable(constexpr constexpr.cpp)
set_target_properties(constexpr PROPERTIES
       CXX_STANDARD 14
       CXX_STANDARD_REQUIRED ON
       )  

add_executable(literal literal.cpp)
set_target_properties(literal PROPERTIES
       CXX_STANDARD 14
       CXX_STANDARD_REQUIRED ON
       )  

add_executable(incapsulation incapsulation.cpp)
set_target_properties(incapsulation PROPERTIES
       CXX_STANDARD 14
       CXX_STANDARD_REQUIRED ON
       )  

add_executable(virtual_destructor virtual_destructor.cpp)
set_target_properties(virtual_destructor PROPERTIES
       CXX_STANDARD 14
       CXX_STANDARD_REQUIRED ON
       )  

add_executable(constexpr_literal constexpr_literal.cpp)
set_target_properties(constexpr_literal PROPERTIES
              CXX_STANDARD 14
              CXX_STANDARD_REQUIRED ON
              )  
cmake_minimum_required(VERSION 3.5)

project(Examples_04)


add_executable(enum enum.cpp)
set_target_properties(enum PROPERTIES
       CXX_STANDARD 14
       CXX_STANDARD_REQUIRED ON
       )

add_executable(exceptions exceptions.cpp)
set_target_properties(exceptions PROPERTIES
       CXX_STANDARD 14
       CXX_STANDARD_REQUIRED ON
       )  


add_executable(return_error return_error.cpp)
set_target_properties(return_error PROPERTIES
       CXX_STANDARD 14
       CXX_STANDARD_REQUIRED ON
       )  

add_executable(custom_exception custom_exception.cpp)
set_target_properties(custom_exception PROPERTIES
       CXX_STANDARD 14
       CXX_STANDARD_REQUIRED ON
       )  

add_executable(complex_exception complex_exception.cpp)
set_target_properties(complex_exception PROPERTIES
       CXX_STANDARD 14
       CXX_STANDARD_REQUIRED ON
       )  

add_executable(exception_in_catch exception_in_catch.cpp)
set_target_properties(exception_in_catch PROPERTIES
       CXX_STANDARD 14
       CXX_STANDARD_REQUIRED ON
       )  

add_executable(noexcept noexcept.cpp)
set_target_properties(noexcept PROPERTIES
       CXX_STANDARD 14
       CXX_STANDARD_REQUIRED ON
       )  

add_executable(terminate terminate.cpp)
set_target_properties(terminate PROPERTIES
       CXX_STANDARD 14
       CXX_STANDARD_REQUIRED ON
       )  

add_executable(namespaces namespaces.cpp)
set_target_properties(namespaces PROPERTIES
       CXX_STANDARD 14
       CXX_STANDARD_REQUIRED ON
       )  

add_executable(ex_fast ex_fast.cpp)
set_target_properties(ex_fast PROPERTIES
              CXX_STANDARD 14
              CXX_STANDARD_REQUIRED ON
              )     
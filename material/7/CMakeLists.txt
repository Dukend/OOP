cmake_minimum_required(VERSION 3.5)

project(Examples_08)


add_executable(variant variant.cpp)
set_target_properties(variant PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
        )

add_executable(abstraction_leak_1 abstraction_leak_1.cpp)
set_target_properties(abstraction_leak_1 PROPERTIES
       CXX_STANDARD 14
       CXX_STANDARD_REQUIRED ON
       )

add_executable(abstraction_leak_2 abstraction_leak_2.cpp)
set_target_properties(abstraction_leak_2 PROPERTIES
       CXX_STANDARD 14
       CXX_STANDARD_REQUIRED ON
       )

add_executable(abstraction_leak_3 abstraction_leak_3.cpp)
set_target_properties(abstraction_leak_3 PROPERTIES
       CXX_STANDARD 14
       CXX_STANDARD_REQUIRED ON
       )
       
add_executable(lambda_1 lambda_1.cpp)
set_target_properties(lambda_1 PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
        )

add_executable(lambda_2 lambda_2.cpp)
set_target_properties(lambda_2 PROPERTIES
       CXX_STANDARD 14
       CXX_STANDARD_REQUIRED ON
       )

add_executable(lambda_3 lambda_3.cpp)
set_target_properties(lambda_3 PROPERTIES
              CXX_STANDARD 14
              CXX_STANDARD_REQUIRED ON
              )

add_executable(lambda_4 lambda_4.cpp)
set_target_properties(lambda_4 PROPERTIES
              CXX_STANDARD 14
              CXX_STANDARD_REQUIRED ON
              )


add_executable(lambda_5 lambda_5.cpp)
set_target_properties(lambda_5 PROPERTIES
              CXX_STANDARD 17
              CXX_STANDARD_REQUIRED ON
              )

add_executable(functional_1 functional_1.cpp)
              set_target_properties(functional_1 PROPERTIES
              CXX_STANDARD 14
              CXX_STANDARD_REQUIRED ON
              )

add_executable(for_each for_each.cpp)
              set_target_properties(for_each PROPERTIES
              CXX_STANDARD 14
              CXX_STANDARD_REQUIRED ON
              )

add_executable(transform transform.cpp)
              set_target_properties(transform PROPERTIES
              CXX_STANDARD 14
              CXX_STANDARD_REQUIRED ON
              )

add_executable(parameter_function parameter_function.cpp)
              set_target_properties(parameter_function PROPERTIES
              CXX_STANDARD 14
              CXX_STANDARD_REQUIRED ON
              )

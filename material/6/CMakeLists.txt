cmake_minimum_required(VERSION 3.5)

project(Examples_06)


add_executable(laba_04_2020 laba_04_2020.cpp)
set_target_properties(laba_04_2020 PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
        )

add_executable(lr_04 lr_04.cpp)
set_target_properties(lr_04 PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
        )

add_executable(variadic_1 variadic_1.cpp)
set_target_properties(variadic_1 PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
        )

add_executable(basic_tuple basic_tuple.cpp)
set_target_properties(basic_tuple PROPERTIES
       CXX_STANDARD 14
       CXX_STANDARD_REQUIRED ON
       )

add_executable(tuple tuple.cpp)
set_target_properties(tuple PROPERTIES
       CXX_STANDARD 17
       CXX_STANDARD_REQUIRED ON
       )

add_executable(crtp crtp.cpp)
set_target_properties(crtp PROPERTIES
       CXX_STANDARD 14
       CXX_STANDARD_REQUIRED ON
       )

add_executable(enable_if enable_if.cpp)
set_target_properties(enable_if PROPERTIES
       CXX_STANDARD 14
       CXX_STANDARD_REQUIRED ON
       )                                                              

add_executable(type_traits type_traits.cpp)
set_target_properties(type_traits PROPERTIES
       CXX_STANDARD 14
       CXX_STANDARD_REQUIRED ON
       ) 

add_executable(variadic_2 variadic_2.cpp)
set_target_properties(variadic_2 PROPERTIES
       CXX_STANDARD 14
       CXX_STANDARD_REQUIRED ON
       ) 

add_executable(template_parameter template_parameter.cpp)
set_target_properties(template_parameter PROPERTIES
       CXX_STANDARD 14
       CXX_STANDARD_REQUIRED ON
       ) 

add_executable(alias alias.cpp)
set_target_properties(alias PROPERTIES
       CXX_STANDARD 14
       CXX_STANDARD_REQUIRED ON
       ) 

add_executable(explicit explicit.cpp explicit_main.cpp)
set_target_properties(explicit PROPERTIES
       CXX_STANDARD 14
       CXX_STANDARD_REQUIRED ON
       ) 

add_executable(constexpr_if constexpr_if.cpp)
set_target_properties(constexpr_if PROPERTIES
       CXX_STANDARD 17
       CXX_STANDARD_REQUIRED ON
       )

add_executable(constexpr_if_tuple constexpr_if_tuple.cpp)
set_target_properties(constexpr_if_tuple PROPERTIES
       CXX_STANDARD 17
       CXX_STANDARD_REQUIRED ON
       )
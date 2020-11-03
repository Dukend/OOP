cmake_minimum_required(VERSION 3.5)

project(Examples_05)


add_executable(for for.cpp)
set_target_properties(for PROPERTIES
       CXX_STANDARD 14
       CXX_STANDARD_REQUIRED ON
       )  
       
add_executable(auto auto.cpp)
set_target_properties(auto PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
        )
        
add_executable(simple_template simple_template.cpp)
set_target_properties(simple_template PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
        )

add_executable(two_arguments two_arguments.cpp)
set_target_properties(two_arguments PROPERTIES
       CXX_STANDARD 14
       CXX_STANDARD_REQUIRED ON
       )

add_executable(array array.cpp)
set_target_properties(array PROPERTIES
       CXX_STANDARD 14
       CXX_STANDARD_REQUIRED ON
       )

add_executable(class_specialization class_specialization.cpp)
set_target_properties(class_specialization PROPERTIES
       CXX_STANDARD 14
       CXX_STANDARD_REQUIRED ON
       )

       add_executable(factorial factorial.cpp)
set_target_properties(factorial PROPERTIES
       CXX_STANDARD 14
       CXX_STANDARD_REQUIRED ON
       )

add_executable(override override.cpp)
set_target_properties(override PROPERTIES
       CXX_STANDARD 14
       CXX_STANDARD_REQUIRED ON
       )

add_executable(partial_specialization partial_specialization.cpp)
set_target_properties(partial_specialization PROPERTIES
              CXX_STANDARD 14
              CXX_STANDARD_REQUIRED ON
              )
       
add_executable(abs abs.cpp)
set_target_properties(abs PROPERTIES
              CXX_STANDARD 14
              CXX_STANDARD_REQUIRED ON
              )                                              
      
add_executable(types types.cpp)
set_target_properties(types PROPERTIES
              CXX_STANDARD 14
              CXX_STANDARD_REQUIRED ON
              ) 
     
add_executable(inheretance inheretance.cpp)
set_target_properties(inheretance PROPERTIES
              CXX_STANDARD 14
              CXX_STANDARD_REQUIRED ON
              )                                              
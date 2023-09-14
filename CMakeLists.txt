cmake_minimum_required(VERSION 3.27.4)

project(set CXX)

include_directories(include)

#smart_pointers library
add_library(smart_pointers include/smart_pointers.h src/smart_pointers.cpp)
target_link_libraries(smart_pointers)

#node
add_library(node include/node.h src/node.cpp)
target_link_libraries(node smart_pointers)

#set
add_subdirectory(modules/Pair)
add_library(set include/node.h src/node.cpp)
target_include_directories(set modules/Pair/include)
target_link_libraries(set node array)

#tesing
option(TEST "Enable google tests" OFF)

if(TEST)

    add_subdirectory(modules/googletest)
    set(TEST_LIBS gmock gmock_main gtest gtest_main)
    set(TEST_INCLUDE modules/googletest/googletest/include modules/googletest/googlemock/include)

    #smart_pointers
    add_executable(gtest_smart_pointers test/gtest_smart_pointers.cpp)
    target_include_directories(gtest_smart_pointers PUBLIC include ${TEST_INCLUDE})
    target_link_libraries(gtest_smart_pointers smart_pointers ${TEST_LIBS})    

    #node
    add_executable(gtest_node test/gtest_node.cpp)
    target_include_directories(gtest_node PUBLIC include ${TEST_INCLUDE})
    target_link_libraries(gtest_node node ${TEST_LIBS})

endif()

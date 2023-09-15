cmake_minimum_required(VERSION 3.27.4)

project(set CXX)

include_directories(include)

#node
add_library(node include/node.h src/node.cc)
target_link_libraries(node memory)

#set
add_subdirectory(modules/STL)
add_library(set include/set.h src/set.cc)
target_include_directories(set PUBLIC modules/STL/include)
target_link_libraries(set node vector)

#tesing
option(GTEST_SET "Enable google tests" OFF)

if(GTEST_SET)

    add_subdirectory(modules/googletest)
    set(TEST_LIBS gmock gmock_main gtest gtest_main)
    set(TEST_INCLUDE modules/googletest/googletest/include modules/googletest/googlemock/include)

    #node
    add_executable(gtest_node test/gtest_node.cpp)
    target_include_directories(gtest_node PUBLIC include ${TEST_INCLUDE})
    target_link_libraries(gtest_node node ${TEST_LIBS})

endif()

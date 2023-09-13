cmake_minimum_required(VERSION 3.27.4)

project(set CXX)

include_directories(include)

#smart_pointers library
add_library(smart_pointers include/smart_pointers.h src/smart_pointers.cpp)
target_link_libraries(smart_pointers)

option(TESTING "Enable google tests" OFF)

if(TESTING)
    add_subdirectory(modules/googletest)
    set(TEST_LIBS gmock gmock_main gtest gtest_main)

    add_executable(gtest_smart_pointers test/gtest_smart_pointers.cpp)
    target_include_directories(gtest_smart_pointers PUBLIC include)
    target_link_libraries(gtest_smart_pointers smart_pointers)
endif()


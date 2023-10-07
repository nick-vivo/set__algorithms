cmake_minimum_required(VERSION 3.27.4)

project(set CXX)

include_directories(include)

add_subdirectory(modules/STL)
include_directories(modules/STL/include)


set(SETHH_LIB include/set.hh src/set.cc)
add_library(sethh ${SETHH_LIB})
target_include_directories(sethh PUBLIC modules/STL/include)
target_link_libraries(sethh set exception)


#main.cpp
add_executable(main main.cpp)
target_include_directories(main PUBLIC modules/STL/include)
target_link_libraries(main set)



# #tesing
# option(GTEST_SET "Enable google tests" OFF)


# if(GTEST_SET)

#     add_subdirectory(modules/googletest)
#     set(TEST_LIBS gmock gmock_main gtest gtest_main)
#     set(TEST_INCLUDE modules/googletest/googletest/include modules/googletest/googlemock/include)

#     #node
#     add_executable(gtest_node test/gtest_node.cpp)
#     target_include_directories(gtest_node PUBLIC include ${TEST_INCLUDE})
#     target_link_libraries(gtest_node node ${TEST_LIBS})

#     #set
#     add_executable(gtest_set test/gtest_set.cpp)
#     target_include_directories(gtest_set PUBLIC include ${TEST_INCLUDE})
#     target_link_libraries(gtest_set set ${TEST_LIBS})

# endif()

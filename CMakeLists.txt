cmake_minimum_required(VERSION 3.16.3)
project(bigint)

set(CMAKE_CXX_STANDARD 20)

add_executable(04 main.cpp bigint.cpp bigint.hpp)

add_executable(test04 test_bigint.cpp bigint.cpp bigint.hpp)

target_link_libraries(test04 gtest_main)
target_link_libraries(test04 gtest)
target_link_libraries(test04 pthread)

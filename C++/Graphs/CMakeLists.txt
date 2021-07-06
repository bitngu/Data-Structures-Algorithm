cmake_minimum_required(VERSION 3.15)
project(hw5)

set(CMAKE_CXX_STANDARD 11)

add_executable(hw5 graph.cpp graph.hpp test_utils.hpp test_utils.cpp test_visible.cpp main.cpp)
cmake_minimum_required(VERSION 3.15)
project(hw3)

set(CMAKE_CXX_STANDARD 11)

add_executable(hw3 priorityqueue.cpp priorityqueue.h json.hpp buildheap.cxx createteams.cxx teamdata.cpp teamdata.h)
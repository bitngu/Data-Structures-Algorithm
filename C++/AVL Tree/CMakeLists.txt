cmake_minimum_required(VERSION 3.15)
project(Prompt)

set(CMAKE_CXX_STANDARD 11)

add_executable(Prompt BST.h BST.cpp json.hpp AVL.cpp AVL.h AVLCommands.cxx)
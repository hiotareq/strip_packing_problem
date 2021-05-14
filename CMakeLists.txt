cmake_minimum_required(VERSION 3.19)
project(strip_packing_problem)

set(CMAKE_CXX_STANDARD 20)

add_executable(strip_packing_problem main.cpp rectangle.cpp rectangle.h plate.cpp plate.h)
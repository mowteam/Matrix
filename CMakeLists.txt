cmake_minimum_required(VERSION 3.25)
project(RealMatrix)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)

add_executable(RealMatrix
        src/main.cpp
        src/matrix.cpp
        src/matrix.h)

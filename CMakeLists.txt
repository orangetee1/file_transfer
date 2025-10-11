cmake_minimum_required(VERSION 3.31)
project(lab2)

set(CMAKE_CXX_STANDARD 20)

add_executable(lab2 main.cpp
        src/utils/ServerSocket.cpp
        src/utils/ServerSocket.h
        src/include/Constants.h)

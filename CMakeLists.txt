cmake_minimum_required(VERSION 3.31)
project(lab2)

set(CMAKE_CXX_STANDARD 20)

add_executable(lab2 main.cpp
        src/net/ServerSocket.cpp
        src/net/ServerSocket.h
        src/include/Constants.h
        src/server/Server.cpp
        src/server/Server.h
        src/net/ClientSocket.cpp
        src/net/ClientSocket.h
        src/server/ServerState.cpp
        src/server/ServerState.h)

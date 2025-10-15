cmake_minimum_required(VERSION 3.31)
project(lab2)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS "-g")

add_executable(lab2 main.cpp
        src/net/ServerSocket.cpp
        src/net/ServerSocket.h
        src/include/Constants.h
        src/server/Server.cpp
        src/server/Server.h
        src/net/ClientSocket.cpp
        src/net/ClientSocket.h
        src/server/ServerState.cpp
        src/server/ServerState.h
        src/server/ServerConnection.cpp
        src/server/ServerConnection.h
        src/server/FileHandler.cpp
        src/server/FileHandler.h
        src/client/Client.cpp
        src/client/Client.h
        src/protocol/server_messages/InitMessage.h
        src/protocol/server_messages/MessageType.h
        src/protocol/MessageHeader.h
        src/protocol/ProtocolBase.h
        src/net/ConnectionState.cpp
        src/net/ConnectionState.h
        src/protocol/server_messages/TransMessage.h
        src/protocol/server_messages/EndMessage.h
        src/protocol/protocol_v1/ProtocolV1Base.cpp
        src/protocol/protocol_v1/ProtocolV1Base.h
        src/server/ClientStats.h
)
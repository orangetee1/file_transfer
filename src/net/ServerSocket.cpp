//
// Created by orangetee on 10/11/25.
//

#include "ServerSocket.h"

#include <stdexcept>
#include <unistd.h>
#include <arpa/inet.h>

#include "../include/Constants.h"

ServerSocket::ServerSocket(int port) {
    sockaddr_in server_address{};
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port);
    server_address.sin_addr.s_addr = INADDR_ANY;

    if ((server_socket_ = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        throw std::runtime_error("socket failed");
    }

    if (bind(server_socket_, reinterpret_cast<sockaddr*>(&server_address),
        sizeof(server_address))) {
        throw std::runtime_error("bind failed");
    }

    if (listen(server_socket_, kDefaultBacklog) < 0) {
        throw std::runtime_error("listen failed");
    }
}

ServerSocket::~ServerSocket() {
    if (close(server_socket_) < 0) {
        throw std::runtime_error("close failed");
    }
}

int ServerSocket::getSocket() {
    return server_socket_;
}


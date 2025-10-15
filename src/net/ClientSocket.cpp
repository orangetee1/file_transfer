//
// Created by orangetee on 10/11/25.
//

#include "ClientSocket.h"

#include <iostream>
#include <stdexcept>
#include <arpa/inet.h>
#include <bits/ostream.tcc>
#include <sys/socket.h>

ClientSocket::ClientSocket() {
    if ((client_socket_ = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        throw std::runtime_error("socket failed");
    }
}

void ClientSocket::setConnection(std::string &address, int port) {
    sockaddr_in server_address{};
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port);
    inet_pton(AF_INET, address.c_str(), &server_address.sin_addr);

    if (connect(client_socket_, reinterpret_cast<sockaddr*>(&server_address),
        sizeof(server_address)) < 0) {
        throw std::runtime_error("connect failed");
    }
}

int ClientSocket::getSocket() {
    return client_socket_;
}

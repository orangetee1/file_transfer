//
// Created by orangetee on 10/11/25.
//

#include "ConnectionHandler.h"

#include <iostream>
#include <sys/socket.h>

ConnectionHandler::ConnectionHandler(int client_socket, int server_socket,
                                     std::shared_ptr<ServerState> ss) :
    client_socket_(client_socket), server_socket_(server_socket),
    server_state_(std::move(ss)) {
    is_transferring_done = false;
    is_connection_closed_by_peer_ = false;
}

// Main work with connection
void ConnectionHandler::handle() {
    std::cout << "thread created" << std::endl;

    while (!is_transferring_done || !is_connection_closed_by_peer_) {
        handle_();

        if (server_state_->getServerState() == 0) {
            break;
        }
    }

    closeClientSocket_();
    std::cout << "thread terminated" << std::endl;
}

void ConnectionHandler::handle_() {

}

void ConnectionHandler::closeClientSocket_() {
    if (close(client_socket_) < 0) {
        std::cout << errno << std::endl;

        throw std::runtime_error("connection handler: close (client socket) failed");
    }
}

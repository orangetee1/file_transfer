//
// Created by orangetee on 10/11/25.
//

#include "Server.h"

Server::Server(int port) :
    server_socket_(std::make_unique<ServerSocket>(port)) {
}

void Server::launch() {
    server_state_->setServerState(1);
}

void Server::setSignalHandler_() {

}

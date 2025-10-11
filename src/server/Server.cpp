//
// Created by orangetee on 10/11/25.
//

#include "Server.h"

void signalHandler(int signal) {
    server_state->setServerState(0);
}

Server::Server(int port) :
    server_socket_(std::make_unique<ServerSocket>(port)) {
    setSignalHandler_();
}

void Server::launch() {
    server_state->setServerState(1);
    mainLoop_();
}

void Server::setSignalHandler_() {
    struct sigaction sa{};
    sa.sa_handler = signalHandler;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGINT, &sa, nullptr);
}

void Server::mainLoop_() {
}

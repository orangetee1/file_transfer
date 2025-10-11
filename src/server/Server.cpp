//
// Created by orangetee on 10/11/25.
//

#include "Server.h"

#include <iostream>
#include <sys/socket.h>

#include "ConnectionHandler.h"

void signalHandler(int signal) {
    server_state->setServerState(0);
}

Server::Server(int port) :
    server_socket_(std::make_unique<ServerSocket>(port)) {
    thread_count_ = 0;
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

void Server::handleConnection_(int client_socket, int server_socket) {
    if (thread_count_ < kDefaultBacklog) {
        ConnectionHandler handler(client_socket, server_socket, server_state);

        threads_[thread_count_] = std::thread(&ConnectionHandler::handle, &handler);

        thread_count_++;
    } else {
        std::cout << "failed handle: too much connections";
    }
}

void Server::mainLoop_() {
    while (server_state->getServerState()) {
        int client_socket;

        if ((client_socket = accept(server_socket_->getSocket(),
            nullptr, nullptr)) < 0) {
            throw std::runtime_error("accept failed");
        }

        handleConnection_(client_socket, server_socket_->getSocket());
    }

    shutdown_();
}

void Server::shutdown_() {
    for (auto &thread : threads_) {
        thread.join();
    }

    std::cout << "Server terminated" << std::endl;
}

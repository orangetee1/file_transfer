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
        auto handler = std::make_shared<ConnectionHandler>(client_socket, server_socket, server_state);

        threads_[thread_count_] = std::thread([handler]() {
            handler->handle();
        });

        thread_count_++;
    } else {
        std::cout << "failed handle: too much connections";
    }
}

void Server::mainLoop_() {
    while (server_state->getServerState()) {
        int client_socket = accept(server_socket_->getSocket(), nullptr, nullptr);

        if (client_socket < 0) {
            throw std::runtime_error("accept failed");
        }

        handleConnection_(client_socket, server_socket_->getSocket());
    }

    shutdown_();
}

void Server::shutdown_() {
    for (auto &thread : threads_) {
        if (thread.joinable())
            thread.join();
    }

    std::cout << "Server terminated" << std::endl;
}

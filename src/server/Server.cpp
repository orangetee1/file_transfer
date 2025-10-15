//
// Created by orangetee on 10/11/25.
//

#include "Server.h"

#include <iostream>
#include <numeric>
#include <sys/socket.h>

#include "ServerConnection.h"

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
    startSpeedThread_();
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
        connections_.push_back(std::make_shared<ServerConnection>(client_socket, server_socket, server_state));
        thread_count_++;
    } else {
        std::cout << "failed handle: too much connections";
    }
}

void Server::mainLoop_() {
    while (server_state->getServerState()) {
        int client_socket = accept(server_socket_->getSocket(), nullptr, nullptr);

        if (client_socket < 0) {
            if (errno == EINTR) {
                std::cout << "Server was stopped" << std::endl;
                break;
            }
            throw std::runtime_error("accept failed");
        }

        handleConnection_(client_socket, server_socket_->getSocket());
    }

    shutdown_();
}

void Server::shutdown_() {
    for (auto& connection : connections_) {
        connection->join();
    }

    speed_monitor_.join();

    std::cout << "Server terminated" << std::endl;
}

void Server::speedThreadFunc_() {
    auto last_check = std::chrono::steady_clock::now();

    while (server_state->getServerState()) {
        std::cout << "[SPEED INFO]" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(3));

        for (auto &connection : connections_) {
            if (!connection->getConnectionState()) continue;

            auto stats = connection->getClientStats();

            auto now = std::chrono::steady_clock::now();
            double interval = std::chrono::duration<double>(now - last_check).count();
            double connection_time = std::chrono::duration<double>(now - stats->connected_at).count();

            double instant_speed = stats->interval_bytes / 1024 / 1024 / interval;
            // connection->addSpeed(instant_speed);
            double average_speed = stats->total_bytes / 1024 / 1024 / connection_time;

            std::cout << "Instant: " << instant_speed << " MB/3s, Average: " << average_speed << " MB/3s\n";

            stats->interval_bytes = 0;
        }
    }
}

void Server::startSpeedThread_() {
    speed_monitor_ = std::thread(&Server::speedThreadFunc_, this);
}

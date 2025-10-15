//
// Created by orangetee on 10/11/25.
//

#ifndef SERVER_H
#define SERVER_H

#include <memory>
#include <array>
#include <thread>

#include "ServerConnection.h"
#include "ServerState.h"
#include "../net/ServerSocket.h"
#include "../include/Constants.h"

inline auto server_state = std::make_shared<ServerState>();

void signalHandler(int signal);

class Server {
public:
    Server(int port);
    void launch();

private:
    // Data
    std::unique_ptr<ServerSocket> server_socket_;
    std::size_t thread_count_;
    std::thread speed_monitor_;
    std::vector<std::shared_ptr<ServerConnection>> connections_;

    // Methods
    void setSignalHandler_();
    void handleConnection_(int client_socket, int server_socket);
    void mainLoop_();
    void shutdown_();
    void speedThreadFunc_();
    void startSpeedThread_();
};



#endif //SERVER_H

//
// Created by orangetee on 10/11/25.
//

#ifndef SERVER_H
#define SERVER_H

#include <memory>
#include <thread>
#include <array>

#include "ServerState.h"
#include "ThreadManager.h"
#include "../include/Constants.h"
#include "../net/ServerSocket.h"

inline auto server_state = std::make_shared<ServerState>();

void signalHandler(int signal);

class Server {
public:
    Server(int port);
    void launch();

private:
    // Data
    std::unique_ptr<ServerSocket> server_socket_;
    std::unique_ptr<ThreadManager> thread_manager_;

    // Methods
    void setSignalHandler_();
    void mainLoop_();
    void handleConnection_();
    void shutdown_();
};



#endif //SERVER_H

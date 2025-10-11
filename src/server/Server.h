//
// Created by orangetee on 10/11/25.
//

#ifndef SERVER_H
#define SERVER_H

#include <memory>

#include "ServerState.h"
#include "../net/ServerSocket.h"

class Server {
public:
    Server(int port);
    void launch();

private:
    // Data
    std::shared_ptr<ServerState> server_state_;
    std::unique_ptr<ServerSocket> server_socket_;

    // Methods
    void setSignalHandler_();
};



#endif //SERVER_H

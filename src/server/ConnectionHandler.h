//
// Created by orangetee on 10/11/25.

#ifndef CONNECTIONHANDLER_H
#define CONNECTIONHANDLER_H

#include <memory>

#include "ServerState.h"

/**
 * Thread class
 */
class ConnectionHandler {
public:
    ConnectionHandler(int client_socket, int server_socket, std::shared_ptr<ServerState> ss);
    void handle();

private:
    // Data
    int client_socket_;
    int server_socket_;
    std::shared_ptr<ServerState> server_state_;
    bool is_transferring_done;

    // Methods
    void handle_();
    void closeClientSocket_();

    void processInitMessage_();
    void processTransMessage_();
    void processEndMessage_();
};



#endif //CONNECTIONHANDLER_H

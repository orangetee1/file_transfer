//
// Created by orangetee on 10/11/25.

#ifndef CONNECTIONHANDLER_H
#define CONNECTIONHANDLER_H

#include <memory>

#include "ConnectionState.h"
#include "FileHandler.h"
#include "ServerState.h"
#include "../protocol/ProtocolBase.h"

class ServerConnection {
public:
    ServerConnection(int client_socket, int server_socket, std::shared_ptr<ServerState> ss);
    void handle();

private:
    // Sockets
    int client_socket_;
    int server_socket_;

    // States
    std::shared_ptr<ServerState> server_state_;
    std::shared_ptr<ConnectionState> connection_state_;
    bool status_;

    // Counts
    uint32_t trans_received_count_{};
    uint64_t bytes_received_{};

    // Utils
    std::unique_ptr<FileHandler> file_handler_;
    std::unique_ptr<ProtocolBase> protocol_base_;

    // Methods
    void handle_();
    void closeClientSocket_();
    void connectionClosedByPeer_();

    void processInitMessage_();
    void processTransMessage_();
    void processEndMessage_();
};



#endif //CONNECTIONHANDLER_H

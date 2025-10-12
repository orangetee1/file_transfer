//
// Created by orangetee on 10/11/25.
//

#include "ServerConnection.h"

#include <iostream>
#include <sys/socket.h>

#include "../include/Constants.h"

ServerConnection::ServerConnection(int client_socket, int server_socket,
                                   std::shared_ptr<ServerState> ss) :
    client_socket_(client_socket), server_socket_(server_socket),
    server_state_(std::move(ss)),
    file_handler_(std::make_unique<FileHandler>()),
    protocol_base_(std::make_unique<ProtocolBase>()) {
    connection_state_->setConnectionState(1);
}

void ServerConnection::handle() {
    std::cout << "thread created" << std::endl;

    while (!connection_state_->getConnectionState()) {
        handle_();

        if (!server_state_->getServerState()) {
            break;
        }
    }

    closeClientSocket_();
    std::cout << "thread terminated" << std::endl;
}

void ServerConnection::handle_() {
    auto header = protocol_base_->getMessageHeader();

    switch (header->type) {
        case MessageType::INIT:
            processInitMessage_();
            break;
        case MessageType::TRANS:
            processTransMessage_();
            break;
        case MessageType::END:
            processEndMessage_();
            break;
    }
}

void ServerConnection::processInitMessage_() {
    auto message = protocol_base_->getInitMessage();

    file_handler_->openFile(message->filename, message->filesize);

    // Send init ack
    protocol_base_->sendAckInit();
}

void ServerConnection::processTransMessage_() {
    auto message = protocol_base_->getTransMessage();

    file_handler_->writeToFile(message->content, message->size);

    if (trans_received_count_ % kTransAckStep == 0) {
        protocol_base_->sendAckTrans();
    }
}

void ServerConnection::processEndMessage_() {
    auto message = protocol_base_->getEndMessage();

    connection_state_->setConnectionState(0);

    protocol_base_->sendStatus(status_);
}

void ServerConnection::closeClientSocket_() {
    if (close(client_socket_) < 0) {
        std::cout << errno << std::endl;
        throw std::runtime_error("connection handler: close (client socket) failed");
    }
}

void ServerConnection::connectionClosedByPeer_() {
    connection_state_->setConnectionState(0);
    std::cout << "connection closed by peer" << std::endl;
}

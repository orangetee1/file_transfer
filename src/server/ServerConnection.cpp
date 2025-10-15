//
// Created by orangetee on 10/11/25.
//

#include "ServerConnection.h"

#include <iostream>
#include <numeric>

#include "../include/Constants.h"
#include "../protocol/protocol_v1/ProtocolV1Base.h"

std::string typeToString(MessageType& type) {
    switch (type) {
        case MessageType::INIT:
            return "INIT";
        case MessageType::TRANS:
            return "TRANS";
        case MessageType::END:
            return "END";
    }
    return "None";
}

ServerConnection::ServerConnection(int client_socket, int server_socket,
                                   std::shared_ptr<ServerState> ss) :
    client_socket_(client_socket), server_socket_(server_socket),
    server_state_(std::move(ss)),
    file_handler_(std::make_unique<FileHandler>()),
    connection_state_(std::make_unique<ConnectionState>()),
    client_stats_(std::make_shared<ClientStats>()),
    protocol_base_(std::make_unique<ProtocolV1Base>(client_socket, connection_state_, client_stats_))
{
    connection_state_->setConnectionState(1);
    client_stats_->connected_at = std::chrono::steady_clock::now();

    connection_thread = std::thread(&ServerConnection::handle, this);
}

void ServerConnection::handle() {
    std::cout << "thread created" << std::endl;

    while (connection_state_->getConnectionState()) {
        if (!connection_state_->getConnectionState()) break;

        handle_();

        if (!server_state_->getServerState()) {
            break;
        }
    }

    auto now = std::chrono::steady_clock::now();
    if (now - client_stats_->connected_at < std::chrono::seconds(3)) {
        printSpeedStat_();
    }

    closeClientSocket_();
    connection_state_->setConnectionState(0);
    std::cout << "thread terminated" << std::endl;
}

void ServerConnection::handle_() {
    auto header = protocol_base_->getMessageHeader();
    if (!header) return;

    switch (header->type) {
        case MessageType::INIT:
            processInitMessage_(header->packet_length);
            break;
        case MessageType::TRANS:
            processTransMessage_(header->packet_length);
            break;
        case MessageType::END:
            processEndMessage_(header->packet_length);
            break;
    }
}

void ServerConnection::processInitMessage_(size_t length) {
    auto message = protocol_base_->getInitMessage(length);

    file_size_ = message->filesize;

    file_handler_->openFile(message->filename, message->filesize);

    protocol_base_->sendAckInit();
}

void ServerConnection::processTransMessage_(size_t length) {
    auto message = protocol_base_->getTransMessage(length);

    file_handler_->writeToFile(message->content, message->size);

    bytes_received_ += message->size;


    int c = message->seq / kTransAckStep;

    if (c == 0)
        protocol_base_->sendAckTrans();
}

ClientStats * ServerConnection::getClientStats() {
    return client_stats_.get();
}

void ServerConnection::join() {
    if (connection_thread.joinable()) {
        std::cout << "Thread join" << std::endl;
        connection_thread.join();
    }
}

int ServerConnection::getConnectionState() {
    return connection_state_->getConnectionState();
}

void ServerConnection::addSpeed(double speed) {
    speeds_.push_back(speed);
}

double ServerConnection::getAverageSpeed() {
    double sum = std::accumulate(speeds_.begin(), speeds_.end(), 0.0);
    return sum / speeds_.size();
}

void ServerConnection::processEndMessage_(size_t length) {
    auto message = protocol_base_->getEndMessage(length);

    bool status = bytes_received_ == file_size_;
    protocol_base_->sendStatus(status);

    connection_state_->setConnectionState(0);
}

void ServerConnection::printSpeedStat_() {
    auto now = std::chrono::steady_clock::now();
    double connection_time = std::chrono::duration<double>(now - client_stats_->connected_at).count();
    double average_speed = client_stats_->total_bytes / 1024 / 1024 / connection_time;
    std::cout << "Average: " << average_speed << " MB/3s\n";
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

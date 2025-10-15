//
// Created by orangetee on 10/12/25.
//

#include "ProtocolV1Base.h"

#include <algorithm>
#include <iostream>

#include "../../server/Server.h"

// TODO: [refactoring] remove repeats of code!!!

ProtocolV1Base::ProtocolV1Base(int socket, std::shared_ptr<ConnectionState> connection_state, std::shared_ptr<ClientStats> client_stats) :
    socket_(socket),
    connection_state_(std::move(connection_state)),
    client_stats_(std::move(client_stats)) {
}

ProtocolV1Base::~ProtocolV1Base() {
}

std::unique_ptr<MessageHeader> ProtocolV1Base::getMessageHeader() {
    std::vector<uint8_t> buffer(kHeaderSize);

    if (!recv_all_(buffer.data(), buffer.size())) {
        return nullptr;
    }

    auto header_p = std::make_unique<MessageHeader>(buffer.data());

    return std::move(header_p);
}

std::unique_ptr<InitMessage> ProtocolV1Base::getInitMessage(size_t length) {
    std::vector<uint8_t> buffer(length);

    if (!recv_all_(buffer.data(), length)) {
        return nullptr;
    }

    auto message_p = std::make_unique<InitMessage>(buffer.data());

    return std::move(message_p);
}

bool ProtocolV1Base::checkAckInit() {
    std::vector<uint8_t> buffer(kHeaderSize);

    if (!recv_all_(buffer.data(), buffer.size())) {
        return false;
    }

    auto header_p = std::make_unique<MessageHeader>(buffer.data());

    return static_cast<bool>(header_p->ack_init);
}

bool ProtocolV1Base::checkAckTrans() {
    std::vector<uint8_t> buffer(kHeaderSize);

    if (!recv_all_(buffer.data(), buffer.size())) {
        return false;
    }

    auto header_p = std::make_unique<MessageHeader>(buffer.data());

    return static_cast<bool>(header_p->ack_trans);
}

std::unique_ptr<TransMessage> ProtocolV1Base::getTransMessage(size_t length) {
    std::vector<uint8_t> buffer(length);

    if (!recv_all_(buffer.data(), length)) {
        return nullptr;
    }

    auto message_p = std::make_unique<TransMessage>(buffer.data());

    return std::move(message_p);
}

std::unique_ptr<EndMessage> ProtocolV1Base::getEndMessage(size_t length) {
    std::vector<uint8_t> buffer(length);

    if (!recv_all_(buffer.data(), length)) {
        return nullptr;
    }

    auto message_p = std::make_unique<EndMessage>(buffer.data());

    return std::move(message_p);
}

void ProtocolV1Base::sendAckInit() {
    MessageHeader header{};
    header.ack_init = 1;
    auto data = header.serialize();

    send_all_(data.data(), data.size());
}

void ProtocolV1Base::sendAckTrans() {
    MessageHeader header{};
    header.ack_trans = 1;
    auto data = header.serialize();

    send_all_(data.data(), data.size());
}

void ProtocolV1Base::sendStatus(bool value) {
    MessageHeader header{};
    header.success = value;
    auto data = header.serialize();
    send_all_(data.data(), data.size());
}

bool ProtocolV1Base::recv_all_(uint8_t *buffer, size_t length) {
    size_t total_received = 0;

    while (total_received < length) {
        ssize_t bytes_received = recv(socket_, buffer + total_received, length - total_received, 0);
        if (bytes_received <= 0) {
            if (bytes_received == 0) std::cout << "Connection closed by peer" << std::endl;
            else std::cout << "recv failed" << std::endl;
            connection_state_->setConnectionState(0);
            return false;
        }

        client_stats_->total_bytes += bytes_received;
        client_stats_->interval_bytes += bytes_received;

        total_received += bytes_received;
    }

    return true;

}

bool ProtocolV1Base::send_all_(uint8_t *buffer, size_t length) {
    size_t total_sent = 0;

    while (total_sent < length) {
        ssize_t sent = send(socket_, buffer + total_sent, length - total_sent, 0);
        if (sent <= 0) {
            std::cout << "Connection closed by peer" << std::endl;
            server_state->setServerState(0);
            return false;
        }
        total_sent += sent;
    }
    return true;
}

void ProtocolV1Base::sendInitMessage(InitMessage *message) {
    auto message_data = message->serialize();

    MessageHeader header{};
    header.type = MessageType::INIT;
    header.packet_length = message_data.size();
    auto header_data = header.serialize();

    send_all_(header_data.data(), header_data.size());

    send_all_(message_data.data(), message_data.size());
}

void ProtocolV1Base::sendTransMessage(TransMessage *message) {
    auto message_data = message->serialize();

    MessageHeader header{};
    header.type = MessageType::TRANS;
    header.packet_length = message_data.size();
    auto header_data = header.serialize();

    send_all_(header_data.data(), header_data.size());
    send_all_(message_data.data(), message_data.size());
}

void ProtocolV1Base::sendEndMessage(EndMessage *message) {
    auto message_data = message->serialize();

    MessageHeader header{};
    header.type = MessageType::END;
    header.packet_length = message_data.size();
    auto header_data = header.serialize();

    send_all_(header_data.data(), header_data.size());
    send_all_(message_data.data(), message_data.size());
}

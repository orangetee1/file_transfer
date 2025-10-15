//
// Created by orangetee on 10/11/25.
//

#include "Client.h"

#include <algorithm>
#include <filesystem>
#include <iostream>
#include <thread>

#include "../protocol/protocol_v1/ProtocolV1Base.h"
#include "../include/Constants.h"

Client::Client(std::string &address, int port, std::string &filename) {
    auto client_stats = std::make_shared<ClientStats>();

    client_socket_ = std::make_unique<ClientSocket>();

    if (!std::filesystem::exists(filename)) {
        std::cerr << "File " << filename << " does not exist";
        return;
    }

    filename_ = filename;
    connection_state_ = std::make_shared<ConnectionState>();
    connection_state_->setConnectionState(1);
    client_socket_->setConnection(address, port);
    file_stream_ = std::ifstream(filename, std::ios::binary);
    protocol_base_ = std::make_unique<ProtocolV1Base>(client_socket_->getSocket(), std::move(connection_state_), std::move(client_stats));
}

void Client::launch() {
    std::filesystem::path file_path(filename_);

    char buffer[kTransferSize];

    InitMessage message{};
    message.filename = file_path.filename();
    message.filesize = std::filesystem::file_size(filename_);

    protocol_base_->sendInitMessage(&message);

    if (!protocol_base_->checkAckInit()) {
        std::cout << "There's no ACK_INIT" << std::endl;
    }

    TransMessage trans_message{};

    uint32_t seq = 0;

    while (file_stream_) {
        // std::cout << "Seq: " << seq << std::endl;
        file_stream_.read(buffer, kTransferSize);
        std::streamsize bytesRead = file_stream_.gcount();
        if (bytesRead > 0) {
            trans_message.content = std::string(buffer, bytesRead);
            trans_message.seq = seq;
            trans_message.size = bytesRead;
            protocol_base_->sendTransMessage(&trans_message);

            int c = seq / kTransAckStep;

            if (c == 0)
                if (!protocol_base_->checkAckTrans()) {
                    std::cout << "ACK_TRANS did not arrive" << std::endl;
                    break;
                }
        }

        seq++;
    }

    EndMessage end_message{};
    protocol_base_->sendEndMessage(&end_message);

    auto status_header = protocol_base_->getMessageHeader();
    std::cout << "Status:" << static_cast<int>(status_header->success) << std::endl;
}

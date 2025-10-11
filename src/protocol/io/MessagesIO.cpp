//
// Created by orangetee on 10/11/25.
//

#include "MessagesIO.h"

#include <cstring>
#include <stdexcept>
#include <netinet/in.h>
#include <sys/socket.h>

#include "../../include/Constants.h"
#include "../messages/Header.h"

Header MessagesIO::recvHeader(int socket, int *status) {
    Header header{};
    int err = recv(socket, &header, sizeof(header), 0);
    if (err < 0) {
        throw std::runtime_error("recv failed (header message)");
    }

    *status = err;

    return header;
}

void MessagesIO::sendInitMessage(int socket, std::string filename, uint64_t filesize) {
    if (filename.size() > kMaxFileNameSize) {
        throw std::runtime_error("messages io: filename size is too big");
    }

    if (filesize > kMaxFileSize) {
        throw std::runtime_error("messages io: file size is too big");
    }

    InitMessage message{};
    message.filesize = htonl(filesize);
    strcpy(message.filename, filename.c_str());

    Header header{};
    header.type = MessageType::INIT;

    int err = send(socket, &header, sizeof(header), 0);
    if (err < 0) {
        // TODO: replace throw with smth better
        throw std::runtime_error("message io (send init message): send failed");
    }

    err = send(socket, &message, sizeof(message), 0);
    if (err < 0) {
        throw std::runtime_error("message io (send init message): send failed");
    }
}

InitMessage MessagesIO::recvInitMessage(int socket, int *status) {
    InitMessage message;
    *status = recv(socket, &message, sizeof(message), 0);

    if (*status < 0) {
        throw std::runtime_error("recv failed (init message)");
    }

    return message;
}

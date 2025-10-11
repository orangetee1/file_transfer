//
// Created by orangetee on 10/11/25.
//

#ifndef MESSAGESIO_H
#define MESSAGESIO_H

#include <string>

#include "../messages/InitMessage.h"
#include "../messages/Header.h"

class MessagesIO {
public:
    static Header recvHeader(int socket, int *status);

    static void sendInitMessage(int socket, std::string filename, uint64_t filesize);
    static InitMessage recvInitMessage(int socket, int *status);
};



#endif //MESSAGESIO_H

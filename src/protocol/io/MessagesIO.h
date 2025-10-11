//
// Created by orangetee on 10/11/25.
//

#ifndef MESSAGESIO_H
#define MESSAGESIO_H

#include <string>

#include "../messages/InitMessage.h"

class MessagesIO {
public:
    void sendInitMessage(int socket, std::string filename, uint64_t filesize);
    InitMessage recvInitMessage(int socket, int *status);
};



#endif //MESSAGESIO_H

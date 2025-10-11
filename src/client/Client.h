//
// Created by orangetee on 10/11/25.
//

#ifndef CLIENT_H
#define CLIENT_H

#include <memory>

#include "../net/ClientSocket.h"

class Client {

private:
    std::unique_ptr<ClientSocket> client_socket_;
};



#endif //CLIENT_H

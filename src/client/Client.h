//
// Created by orangetee on 10/11/25.
//

#ifndef CLIENT_H
#define CLIENT_H

#include <memory>
#include <string>
#include <fstream>

#include "../net/ClientSocket.h"
#include "../net/ConnectionState.h"
#include "../protocol/ProtocolBase.h"

class Client {
public:
    Client(std::string& address, int port, std::string& filename);
    void launch();

private:
    std::shared_ptr<ConnectionState> connection_state_;
    std::unique_ptr<ClientSocket> client_socket_;
    std::unique_ptr<ProtocolBase> protocol_base_;
    std::ifstream file_stream_;
    std::string filename_;
};



#endif //CLIENT_H

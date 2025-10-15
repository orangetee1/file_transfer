//
// Created by orangetee on 10/11/25.
//

#ifndef CLIENTSOCKET_H
#define CLIENTSOCKET_H

#include <string>

class ClientSocket {
public:
    ClientSocket();
    void setConnection(std::string& address, int port);
    int getSocket();

private:
    int client_socket_;
};



#endif //CLIENTSOCKET_H

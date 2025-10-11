//
// Created by orangetee on 10/11/25.
//

#ifndef SERVERSTATE_H
#define SERVERSTATE_H

#include <csignal>

class ServerState {
public:
    void setServerState(int value);
    int getServerState();

private:
    volatile sig_atomic_t server_state_;
};



#endif //SERVERSTATE_H

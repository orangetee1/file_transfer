//
// Created by orangetee on 10/11/25.
//

#include "ServerState.h"

#include <iostream>

void ServerState::setServerState(int value) {
    if (value != 0 && value != 1) {
        std::cerr << "server state can be 0 or 1" << std::endl;
        return;
    }

    server_state_ = value;
}

int ServerState::getServerState() {
    return server_state_;
}

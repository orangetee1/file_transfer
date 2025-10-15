//
// Created by orangetee on 10/12/25.
//

#include "ConnectionState.h"

#include <iostream>

void ConnectionState::setConnectionState(const int value) {
    if (value != 0 && value != 1) {
        std::cerr << "server state can be 0 or 1" << std::endl;
        return;
    }

    connection_state_ = value;
}

int ConnectionState::getConnectionState() {
    return connection_state_;
}

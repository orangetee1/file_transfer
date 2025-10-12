//
// Created by orangetee on 10/12/25.
//

#ifndef CONNECTIONSTATE_H
#define CONNECTIONSTATE_H

#include <csignal>

class ConnectionState {
public:
    void setConnectionState(int value);
    int getConnectionState();

private:
    volatile sig_atomic_t connection_state_;
};



#endif //CONNECTIONSTATE_H

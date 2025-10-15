//
// Created by orangetee on 10/11/25.

#ifndef CONNECTIONHANDLER_H
#define CONNECTIONHANDLER_H

#include <memory>
#include <thread>

#include "ClientStats.h"
#include "../net/ConnectionState.h"
#include "FileHandler.h"
#include "ServerState.h"
#include "../protocol/ProtocolBase.h"

void alarmSignalHandler();

class ServerConnection {
public:
    ServerConnection(int client_socket, int server_socket, std::shared_ptr<ServerState> ss);
    ClientStats* getClientStats();
    void handle();
    void join();
    int getConnectionState();

    void addSpeed(double speed);
    double getAverageSpeed();

private:
    // Thread
    std::thread connection_thread;

    // Sockets
    int client_socket_;
    int server_socket_;

    // States
    std::shared_ptr<ServerState> server_state_;
    std::shared_ptr<ConnectionState> connection_state_;
    std::shared_ptr<ClientStats> client_stats_;

    // Counts
    uint32_t trans_received_count_{0};
    uint64_t bytes_received_{0};
    uint64_t file_size_{};

    // Utils
    std::unique_ptr<FileHandler> file_handler_;
    std::unique_ptr<ProtocolBase> protocol_base_;

    std::vector<double> speeds_;

    // Methods
    void handle_();
    void closeClientSocket_();
    void connectionClosedByPeer_();

    void processInitMessage_(size_t length);
    void processTransMessage_(size_t length);
    void processEndMessage_(size_t length);

    void printSpeedStat_();
};



#endif //CONNECTIONHANDLER_H

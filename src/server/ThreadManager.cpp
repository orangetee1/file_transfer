//
// Created by orangetee on 10/11/25.
//

#include "ThreadManager.h"

void ThreadManager::shutDown() {
    for (auto &thread : threads_) {
        thread.join();
    }

}

void ThreadManager::handleConnection(int client_socket, int server_socket) {

}

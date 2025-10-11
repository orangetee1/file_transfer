//
// Created by orangetee on 10/11/25.
//

#ifndef THREADMANAGER_H
#define THREADMANAGER_H

#include <thread>
#include <array>

#include "../include/Constants.h"

class ThreadManager {
public:
    ~ThreadManager();

private:
    std::array<std::thread, kDefaultBacklog> threads_;
};



#endif //THREADMANAGER_H

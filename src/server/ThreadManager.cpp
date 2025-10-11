//
// Created by orangetee on 10/11/25.
//

#include "ThreadManager.h"

ThreadManager::~ThreadManager() {
    for (auto &thread : threads_) {
        thread.join();
    }
}
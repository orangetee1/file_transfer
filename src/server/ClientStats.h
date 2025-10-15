//
// Created by orangetee on 10/15/25.
//

#ifndef CLIENTSTATS_H
#define CLIENTSTATS_H

#include <chrono>

struct ClientStats {
    uint64_t total_bytes;
    uint64_t interval_bytes;
    std::chrono::steady_clock::time_point connected_at;
};

#endif //CLIENTSTATS_H

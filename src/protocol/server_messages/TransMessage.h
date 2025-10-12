//
// Created by orangetee on 10/12/25.
//

#ifndef TRANSMESSAGE_H
#define TRANSMESSAGE_H

#include <vector>
#include <cstdint>

struct TransMessage {
    // Constructors
    TransMessage() = default;
    TransMessage(uint8_t *data);

    // Data
    uint32_t seq;
    uint32_t size;
    char *content;

    // Methods
    std::vector<uint8_t> serialize();
};

#endif //TRANSMESSAGE_H

//
// Created by orangetee on 10/12/25.
//

#ifndef MESSAGEHEADER_H
#define MESSAGEHEADER_H

#include <vector>
#include <cstdint>

#include "server_messages/MessageType.h"

struct MessageHeader {
    // Constructors
    MessageHeader() = default;
    MessageHeader(uint8_t *data);

    // Data
    MessageType type;
    uint32_t packet_length;

    // Methods
    std::vector<uint8_t> serialize();
};

inline MessageHeader::MessageHeader(uint8_t *data) {
}

inline std::vector<uint8_t> MessageHeader::serialize() {
}

#endif //MESSAGEHEADER_H

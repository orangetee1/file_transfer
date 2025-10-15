//
// Created by orangetee on 10/12/25.
//

#ifndef MESSAGEHEADER_H
#define MESSAGEHEADER_H

#include <vector>
#include <cstring>
#include <netinet/in.h>

#include "server_messages/MessageType.h"

struct MessageHeader {
    // Constructors
    MessageHeader() = default;
    MessageHeader(uint8_t *data);

    // Data
    MessageType type{};
    uint8_t ack_init{0};
    uint8_t ack_trans{0};
    uint8_t success{0};
    uint32_t packet_length{0};

    // Methods
    std::vector<uint8_t> serialize();
};

inline MessageHeader::MessageHeader(uint8_t *data) {
    type = static_cast<MessageType>(data[0]);

    ack_init = data[1];
    ack_trans = data[2];
    success = data[3];

    uint32_t n_packet_length;
    std::memcpy(&n_packet_length, data + 4, 4);
    packet_length = ntohl(n_packet_length);
}

inline std::vector<uint8_t> MessageHeader::serialize() {
    std::vector<uint8_t> buffer;

    buffer.push_back(static_cast<uint8_t>(type));

    buffer.push_back(ack_init);
    buffer.push_back(ack_trans);
    buffer.push_back(success);

    uint32_t n_packet_length = htonl(packet_length);

    auto p = reinterpret_cast<uint8_t*>(&n_packet_length);
    buffer.insert(buffer.end(), p, p + 4);

    return buffer;
}

#endif //MESSAGEHEADER_H

//
// Created by orangetee on 10/12/25.
//

#ifndef TRANSMESSAGE_H
#define TRANSMESSAGE_H

#include <vector>
#include <string>

struct TransMessage {
    // Constructors
    TransMessage() = default;
    TransMessage(uint8_t *data);

    // Data
    uint32_t seq;
    uint32_t size;
    std::string content;

    // Methods
    std::vector<uint8_t> serialize();
};

inline std::vector<uint8_t> TransMessage::serialize() {
    std::vector<uint8_t> buffer;

    uint32_t n_seq = htonl(seq);
    const uint8_t* p = reinterpret_cast<const uint8_t*>(&n_seq);
    buffer.insert(buffer.end(), p, p + 4);

    uint32_t n_size = htonl(size);
    p = reinterpret_cast<const uint8_t*>(&n_size);
    buffer.insert(buffer.end(), p, p + 4);

    buffer.insert(buffer.end(), content.begin(), content.end());

    return buffer;
}

inline TransMessage::TransMessage(uint8_t* data) {
    uint32_t n_seq;
    std::memcpy(&n_seq, data, 4);
    seq = ntohl(n_seq);

    uint32_t n_size;
    std::memcpy(&n_size, data + 4, 4);
    size = ntohl(n_size);

    content.assign(reinterpret_cast<const char*>(data + 8), size);
}


#endif //TRANSMESSAGE_H

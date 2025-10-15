//
// Created by orangetee on 10/12/25.
//

#ifndef INITMESSAGE_H
#define INITMESSAGE_H

#include <string>
#include <vector>

struct InitMessage {
    // Constructors
    InitMessage() = default;
    InitMessage(uint8_t* data);

    // Data
    uint64_t filesize;
    std::string filename;

    // Methods
    std::vector<uint8_t> serialize();
};

inline std::vector<uint8_t> InitMessage::serialize() {
    std::vector<uint8_t> buffer;

    uint64_t n_filesize =
        (static_cast<uint64_t>(htonl(filesize & 0xFFFFFFFF)) << 32) |
        htonl(filesize >> 32);

    auto p = reinterpret_cast<const uint8_t*>(&n_filesize);
    buffer.insert(buffer.end(), p, p + 8);

    uint32_t len = filename.size();
    uint32_t n_len = htonl(len);
    p = reinterpret_cast<const uint8_t*>(&n_len);
    buffer.insert(buffer.end(), p, p + 4);

    buffer.insert(buffer.end(), filename.begin(), filename.end());

    return buffer;
}

inline InitMessage::InitMessage(uint8_t* data) {
    uint64_t n_filesize;
    std::memcpy(&n_filesize, data, 8);
    filesize =
        (static_cast<uint64_t>(ntohl(n_filesize & 0xFFFFFFFF)) << 32) |
        ntohl(n_filesize >> 32);

    uint32_t n_len;
    std::memcpy(&n_len, data + 8, 4);
    uint32_t len = ntohl(n_len);

    filename.assign(reinterpret_cast<const char*>(data + 12), len);
}

#endif //INITMESSAGE_H

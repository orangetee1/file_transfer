//
// Created by orangetee on 10/12/25.
//

#ifndef INITMESSAGE_H
#define INITMESSAGE_H

#include <cstdint>
#include <vector>

struct InitMessage {
    // Constructors
    InitMessage() = default;
    InitMessage(uint8_t* data);

    // Data
    uint64_t filesize;
    char *filename;

    // Methods
    std::vector<uint8_t> serialize();
};

inline InitMessage::InitMessage(uint8_t *data) {

}

inline std::vector<uint8_t> InitMessage::serialize() {

}

#endif //INITMESSAGE_H

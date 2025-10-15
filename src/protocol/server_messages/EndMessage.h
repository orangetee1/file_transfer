//
// Created by orangetee on 10/12/25.
//

#ifndef ENDMESSAGE_H
#define ENDMESSAGE_H

#include <vector>

struct EndMessage {
    // Constructors
    EndMessage() = default;
    EndMessage(uint8_t *data);

    // Data


    // Methods
    std::vector<uint8_t> serialize();
};

inline EndMessage::EndMessage(uint8_t *data) {
}

inline std::vector<uint8_t> EndMessage::serialize() {
    return std::vector<uint8_t>(1);
}

#endif //ENDMESSAGE_H

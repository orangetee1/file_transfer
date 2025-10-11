//
// Created by orangetee on 10/11/25.
//

#ifndef MESSAGETYPE_H
#define MESSAGETYPE_H
#include <cstdint>

enum class MessageType : uint8_t {
    INIT,
    ACK_INIT,
    TRANS,
    ACK_TRANS,
    END,
    END_STATUS,
    SPEED_CHECK
};

#endif //MESSAGETYPE_H

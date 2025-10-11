//
// Created by orangetee on 10/11/25.
//

#ifndef MESSAGETYPE_H
#define MESSAGETYPE_H
#include <cstdint>

enum class MessageType : uint8_t {
    INIT,
    TRANS,
    END
};

#endif //MESSAGETYPE_H

//
// Created by orangetee on 10/11/25.
//

#ifndef TRANSMESSAGE_H
#define TRANSMESSAGE_H

#include <cstdint>

#include "../../include/Constants.h"

struct TransMessage {
    uint32_t seq;
    char content[kTransferSize];
};

#endif //TRANSMESSAGE_H

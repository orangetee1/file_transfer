//
// Created by orangetee on 10/11/25.
//

#ifndef INITMESSAGE_H
#define INITMESSAGE_H

#include <cstdint>

#include "../../include/Constants.h"

struct InitMessage {
    uint64_t filesize;
    char filename[kMaxFileNameSize];
};

#endif //INITMESSAGE_H

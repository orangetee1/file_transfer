//
// Created by orangetee on 10/11/25.
//

#ifndef INITMESSAGE_H
#define INITMESSAGE_H

#include <cstdint>

struct InitMessage {
    uint64_t filesize;
    char filename[4096];
};

#endif //INITMESSAGE_H

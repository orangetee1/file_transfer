//
// Created by orangetee on 10/11/25.
//

#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <cstdint>
#include <string>

constexpr uint8_t kDefaultBacklog = 10;
constexpr uint16_t kMaxFileNameSize = 4096;
constexpr uint64_t kMaxFileSize = 10e12;
constexpr uint64_t kTransferSize = 256 * 1024;

constexpr std::string kFolderName = "uploads";

#endif //CONSTANTS_H

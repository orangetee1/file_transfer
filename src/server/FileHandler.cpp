//
// Created by orangetee on 10/11/25.
//

#include "FileHandler.h"

#include "../include/Constants.h"

FileHandler::FileHandler() : dir_path_(std::filesystem::path(kFolderName)) {
    if (!exists(dir_path_)) {
        std::filesystem::create_directory(dir_path_);
    }
}

FileHandler::~FileHandler() {
    if (file_stream_.is_open()) {
        file_stream_.close();
    }
}

void FileHandler::openFile(const std::string& filename, uint64_t filesize) {
    std::filesystem::path file_path = dir_path_ / filename;

    file_stream_ = std::ofstream(file_path);
}

void FileHandler::writeToFile(char *content, uint32_t content_size) {
    if (file_stream_.is_open()) {
        file_stream_.write(content, content_size);
    }
}


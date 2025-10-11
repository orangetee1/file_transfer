//
// Created by orangetee on 10/11/25.
//

#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <filesystem>
#include <fstream>

class FileHandler {
public:
    FileHandler();
    ~FileHandler();

    void openFile(const std::string& filename, uint64_t filesize);
    void writeToFile(char *content, uint32_t content_size);

private:
    std::filesystem::path dir_path_;
    std::ofstream file_stream_;
};



#endif //FILEHANDLER_H

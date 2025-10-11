#include <cstring>
#include <iostream>

#include "src/server/Server.h"
#include "src/server/FileHandler.h"

void start_server(int argc, char *argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " server <port>" << std::endl;
        std::exit(-1);
    }

    int port = std::stoi(argv[2]);

    Server server(port);
    server.launch();
}

void start_client(int argc, char *argv[]) {
    if (argc != 5) {
        std::cerr << "Usage: " << argv[0] << " client <server_ip> <server_port> <filepath>" << std::endl;
        std::exit(-1);
    }

    std::string server_ip(argv[2]);
    int port = std::stoi(argv[3]);
    std::string filepath(argv[4]);

    // TODO: create client Client copy
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <mode>" << std::endl;
        std::exit(-1);
    }

    std::cout << "Process ID: " << getpid() << std::endl;

    if (std::strcmp(argv[1], "server") == 0) {
        start_server(argc, argv);
    } else if (std::strcmp(argv[1], "client") == 0) {
        start_client(argc, argv);
    }

    return 0;
}
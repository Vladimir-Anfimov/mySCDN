#include <iostream>
#include "ProxyServer.h"

int main(int argc, char** argv) {
    if(argc < 2)
        std::runtime_error("Port is missing from arguments");
    int port = atoi(argv[1]);
    auto server = new ProxyServer(9999);
    server->start_listening();
}
#include <iostream>
#include "./Infrastructure/TcpServer.h"
#include "Print.h"

using namespace Utils::Print;

int main(int argc, char* argv[]) {
    if(argc<2)
        handle_error("Port is missing from args.");
    int node_port = atoi(argv[1]), proxy_port = 9000;
    auto server = new TcpServer(node_port, proxy_port);
    server->start_listening();
}
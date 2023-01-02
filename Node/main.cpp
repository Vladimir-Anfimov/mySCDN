#include <iostream>
#include "./Infrastructure/TcpServer.h"
#include "Print.h"
#include "DataLayer/DatabaseContext.h"
#include "Infrastructure/DeliveryNetwork.h"

using namespace Utils::Print;

int main(int argc, char* argv[]) {
    if(argc<3)
        handle_error("Script format call: [node_port:int] [proxy_port:int]");
    int node_port = atoi(argv[1]), proxy_port = atoi(argv[2]);

    DeliveryNetwork::current_node_port = node_port;
    DatabaseContext::port = node_port;

    auto server = new TcpServer(node_port, proxy_port);
    server->start_listening();
}
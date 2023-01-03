#include <iostream>
#include "./Infrastructure/TcpServer.h"
#include "Print.h"
#include "DataLayer/DatabaseContext.h"
#include "Infrastructure/DeliveryNetwork.h"
#include "BusinessLayer/InitialiseService.h"

using namespace Utils::Print;

int main(int argc, char* argv[]) {
    if(argc<4)
        handle_error("Script format call: [node_port:int] [proxy_port:int] [origin_port:int]");
    int node_port = atoi(argv[1]), proxy_port = atoi(argv[2]), origin_port = atoi(argv[3]);

    std::string db = "node_sql_port_" + std::to_string(node_port) +".db";
    if(std::filesystem::exists(db))
    {
        handle_log("Database %s was initially deleted.", db.c_str());
        std::filesystem::remove(db);
    }

    DatabaseContext::port = node_port;
    DeliveryNetwork::current_node_port = node_port;

    if(node_port != origin_port)
    {
        auto initialise_service = InitialiseService(origin_port);
        initialise_service.initialise();
    }

    auto server = new TcpServer(node_port, proxy_port);
    server->start_listening();
}
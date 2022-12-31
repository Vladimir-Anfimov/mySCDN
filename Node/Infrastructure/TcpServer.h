#pragma once
#include "Server.h"

class TcpServer: public Server {
protected:
    void process_event(ConnectionType client) override;
    std::string handle_request_command(const std::string& command);
public:
    TcpServer(int node_port, int proxy_port);
};
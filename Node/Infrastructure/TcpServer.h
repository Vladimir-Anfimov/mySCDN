#pragma once
#include "Server.h"

class TcpServer: public Server {
protected:
    void process_event(ConnectionType client) override;
    std::string handle_event(const std::string& message);
public:
    TcpServer(int port);
};
#pragma once
#include "Server.h"

class ProxyServer: public Server {
protected:
    void process_event(ConnectionType client) override;
public:
    ProxyServer(int port);
};
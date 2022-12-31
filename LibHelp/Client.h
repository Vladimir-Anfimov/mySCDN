#pragma once

#include <netinet/in.h>
#include "Server.h"

class Client {
private:
    sockaddr_in socket_address_server;
    int socket_descriptor;
    const int server_port;
public:
    explicit Client(int server_port);
    ConnectionType get_connection() const;
    void shutdown_connection();
};
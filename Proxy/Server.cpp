#include <iostream>
#include <unistd.h>
#include "Server.h"
#include "Print.h"

using namespace Utils::Print;

Server::Server(int port): ThreadPool<ConnectionType>(), ServerConfig(port) {
}


void Server::start_listening() {
    auto address_length = sizeof(get_sockaddr_in());
    int connection;

    handle_log("Server is waiting for new connections.");
    while(true)
    {
        connection = accept(
                get_socket_descriptor(),
                (struct sockaddr*)get_sockaddr_in(),
                        (socklen_t*)&address_length);
        if(connection < 0)
        {
            handle_warning("Failed to accept a new connection.");
            continue;
        }
        queue_data(connection);
    }
}

Server::~Server() {
    close(get_socket_descriptor());
}



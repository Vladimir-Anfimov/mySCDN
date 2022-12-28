#include <iostream>
#include <unistd.h>
#include "Server.h"
#include "Print.h"
#include "HttpCommunication.h"

using namespace Utils::Print;

Server::Server(int port): ThreadPool<ConnectionType>(), ServerConfig(port) {
}

void Server::process_event(ConnectionType client) {
    auto communication = HttpCommunication(client);
    try {
        std::string message = communication.read_message();
        handle_log("Message %s\n", message.c_str());
        communication.write_message("hei hei hei\n");
    }
    catch (std::exception& exp)
    {
        handle_warning("%s\n", exp.what());
        communication.write_message(exp.what());
    }
}

Server *Server::get_instance(int port) {
    if(server_instance == nullptr)
        server_instance = new Server(port);
    return server_instance;
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



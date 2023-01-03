#include "Client.h"
#include <iostream>
#include "Print.h"

using namespace Utils::Print;

Client::Client(int server_port): server_port(server_port) {
    if((socket_descriptor = socket(AF_INET, SOCK_STREAM, 0)) == -1)
        throw std::runtime_error("Error at socket in client class.");

    socket_address_server.sin_family = AF_INET;
    socket_address_server.sin_addr.s_addr = htonl(INADDR_ANY);
    socket_address_server.sin_port = htons(server_port);

    if (connect (socket_descriptor,
                 (struct sockaddr *) &socket_address_server,
                         sizeof (struct sockaddr)) == -1)
        throw std::runtime_error("Error when trying to connect in client class");
}

ConnectionType Client::get_connection() const {
    return socket_descriptor;
}

void Client::shutdown_connection() {
    shutdown(socket_descriptor, SHUT_RDWR);
}

Client::~Client() {
    shutdown_connection();
}


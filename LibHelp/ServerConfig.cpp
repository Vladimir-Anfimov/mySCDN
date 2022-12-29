#include "ServerConfig.h"
#include "Print.h"
#include <sys/socket.h>

using namespace Utils::Print;

ServerConfig::ServerConfig(int port, int queue_size):
    port(port),
    queue_size(queue_size)
{
    if((socket_descriptor = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        handle_error("Failed to create the main socket for the server.");

    int on=1;
    setsockopt(socket_descriptor,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on));

    socket_address.sin_family = AF_INET;
    socket_address.sin_addr.s_addr = htonl(INADDR_ANY);
    socket_address.sin_port = htons(port);

    bind_server();
    prepare_listening();
}

void ServerConfig::bind_server() {
    if(bind(socket_descriptor, (struct sockaddr*)&socket_address, sizeof(socket_address)) < 0)
        handle_error("Failed to bind to port %d", port);
}

void ServerConfig::prepare_listening() {
    if(listen(socket_descriptor, queue_size) < 0)
        handle_error("Failed to start listening on port %d with queue size of %d",
                     port, queue_size);
    handle_log("Server is ready to listen on port %d", port);
}

int ServerConfig::get_port() const {
    return port;
}

sockaddr_in* const ServerConfig::get_sockaddr_in() {
    return &socket_address;
}

int ServerConfig::get_socket_descriptor() const {
    return socket_descriptor;
}

#pragma once

#include <netinet/in.h>

class ServerConfig {
private:
    constexpr static int MAXIMUM_QUEUE_SIZE = 100;

    sockaddr_in socket_address;
    int socket_descriptor;
    int port, queue_size;
private:
    void bind_server();
    void prepare_listening();
protected:
    int get_port() const;
    sockaddr_in* const get_sockaddr_in();
    int get_socket_descriptor() const;
public:
    explicit ServerConfig(int port, int queue_size = MAXIMUM_QUEUE_SIZE);
};


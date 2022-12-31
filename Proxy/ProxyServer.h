#pragma once
#include "Server.h"
#include "vector"
#include "./Node.h"
#include "TcpCommunication.h"

class ProxyServer: public Server {
    void process_event(ConnectionType client) override;
    std::string process_command(TcpCommunication* communication,
                                std::string command,
                                bool http);
    void recurrent_node_check();

    std::string round_robin_process(const std::string& command);
    std::string ping_process(const std::string& command);
    std::vector<Node> nodes;
    std::mutex mutex_nodes;
    int round_robin_index = 0;
public:
    ProxyServer(int port);
};
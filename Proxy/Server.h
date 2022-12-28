#pragma once
#include "ThreadPool.h"
#include "ServerConfig.h"

using ConnectionType = int;

class Server:
        public ThreadPool<ConnectionType>,
        public ServerConfig
{
private:
    inline static Server *server_instance;

    void process_event(ConnectionType event_data) override;
    explicit Server(int port);
public:
    static Server* get_instance(int port);
    Server(Server &other) = delete;
    void operator=(const Server&) = delete;
    void start_listening();
    ~Server();
};
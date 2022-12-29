#pragma once
#include "ThreadPool.h"
#include "ServerConfig.h"

using ConnectionType = int;

class Server:
        private ThreadPool<ConnectionType>,
        private ServerConfig
{
protected:
    virtual void process_event(ConnectionType event_data) = 0;
    explicit Server(int port);
public:
    void start_listening();
    ~Server();
};
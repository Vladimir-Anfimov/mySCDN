#pragma once
#include <vector>
#include <thread>

class Server {
protected:
    bool terminate = false;
    std::vector<std::thread> threads;
    int port;

public:
    Server();

};



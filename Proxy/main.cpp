#include <iostream>
#include "ProxyServer.h"

int main(int argc, char** argv) {
    int port = 9000;
    auto server = new ProxyServer(port);
    server->start_listening();
}
#include <iostream>
#include "ProxyServer.h"
#include "Print.h"

using namespace Utils::Print;

int main(int argc, char** argv) {
    if(argc<2)
        handle_error("Script format call: [proxy_port:int]");
    int proxy_port = atoi(argv[1]);

    auto server = new ProxyServer(proxy_port);
    server->start_listening();
}
#include <iostream>
#include "ProxyServer.h"


int main() {
    auto server = new ProxyServer(9999);
    server->start_listening();
}

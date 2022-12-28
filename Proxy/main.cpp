#include <iostream>
#include "Server.h"


int main() {
    auto server = Server::get_instance(9999);
    server->start_listening();
}

#include "ProxyServer.h"
#include "HttpCommunication.h"
#include "Print.h"

using namespace Utils::Print;

void ProxyServer::process_event(ConnectionType client) {
    auto communication = HttpCommunication(client);
    try {
        std::string message = communication.read_message();
        handle_log("Message %s", message.c_str());
        communication.write_message("hei hei hei\n");
    }
    catch (std::exception& exp)
    {
        handle_warning("%s\n", exp.what());
        communication.write_message(exp.what());
    }
    shutdown(client, SHUT_RDWR);
}

ProxyServer::ProxyServer(int port): Server(port) {
}
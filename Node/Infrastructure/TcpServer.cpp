#include "TcpServer.h"
#include "HttpCommunication.h"
#include "Print.h"
#include "../Common/Command.h"
#include "../BusinessLayer/CacheService.h"

using namespace Utils::Print;

TcpServer::TcpServer(int port): Server(port) {
}

void TcpServer::process_event(ConnectionType client) {
    auto communication = TcpCommunication(client);
    try {
        std::string message = communication.read_message();
        handle_log("New Message: %s", message.c_str());

        std::string response = handle_event(message);

        communication.write_message(response);
    }
    catch (std::exception& exp)
    {
        handle_warning("%s\n", exp.what());
        communication.write_message(exp.what());
    }
    shutdown(client, SHUT_RDWR);
}

std::string TcpServer::handle_event(const std::string& message) {
    if(Command::is_search(message))
    {
        auto *cache_service = new CacheService();

    }
    return "";
}

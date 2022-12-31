#include "TcpServer.h"
#include "HttpCommunication.h"
#include "Print.h"
#include "../Common/Command.h"
#include "../BusinessLayer/SearchService.h"
#include "./RecurrentPing.h"

using namespace Utils::Print;

TcpServer::TcpServer(int node_port, int proxy_port): Server(node_port) {
    recurrent_ping(node_port, proxy_port);
}

void TcpServer::process_event(ConnectionType client) {
    auto communication = TcpCommunication(client);
    try {
        std::string message = communication.read_message();
        handle_log("New Message: %s", message.c_str());

        std::string response = handle_request_command(message);

        communication.write_message(response);
    }
    catch (std::exception& exp)
    {
        handle_warning("%s\n", exp.what());
        communication.write_message(exp.what());
    }
    shutdown(client, SHUT_RDWR);
}

std::string TcpServer::handle_request_command(const std::string& command) {
    if(Command::is_search(command))
    {
        auto *search_service = new SearchService();
        return search_service->find_content(command);
    }
    throw std::runtime_error("Command " + command + " not supported.");
}

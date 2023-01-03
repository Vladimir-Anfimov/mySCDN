#include "TcpServer.h"
#include "HttpCommunication.h"
#include "Print.h"
#include "../Common/Command.h"
#include "../BusinessLayer/SearchService.h"
#include "./RecurrentPing.h"
#include "../BusinessLayer/UploadService.h"
#include "RecurrentDeleteOutdatedCache.h"

using namespace Utils::Print;

TcpServer::TcpServer(int node_port, int proxy_port): Server(node_port) {
    recurrent_ping(node_port, proxy_port);
    recurrent_delete_outdated_cache();
}

void TcpServer::process_event(ConnectionType client) {
    auto communication = TcpCommunication(client);
    try {
        std::string message = communication.read_message();
        handle_log("New Message: %s", message.c_str());

        std::string response = handle_request_command(message);

        handle_logG("Response: %s\n", response.c_str());
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
        auto search_service = new SearchService();
        return search_service->find_content(command);
    }
    if(Command::is_upload(command))
    {
        auto *upload_service = new UploadService();
        upload_service->upload_cache_item(command);
        return "Cache item successfully cached.";
    }
    if(Command::is_purge_and_inform(command))
    {
        auto *upload_service = new UploadService();
        upload_service->purge_and_update_external_cache(command);
        return "Cache item was successfully purged and inserted as a reference to another node.";
    }
    if(Command::is_initialise(command))
    {
        auto *upload_service = new UploadService();
        return upload_service->initialise_external_node();
    }
    if(Command::is_new_duplicate(command))
    {
        auto *upload_service = new UploadService();
        upload_service->upload_data_about_new_duplicate_in_network(command);
        return "Information about the new duplicated successfully added.";
    }

    throw std::runtime_error("Command " + command + " not supported.");
}

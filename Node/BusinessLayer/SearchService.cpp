#include <Client.h>
#include <TcpCommunication.h>
#include "SearchService.h"
#include "../DataLayer/CacheRepository.h"
#include "../Common/Command.h"
#include "../Infrastructure/DeliveryNetwork.h"

SearchService::SearchService() {}

std::string SearchService::find_content(const std::string &command) {
    std::string url = Command::get_url_from_search_command(command);
    auto *repository = new CacheRepository();

    auto cache_dto = repository->find_by_value(
            "url", url, "port", DatabaseContext::port);
    if(cache_dto != nullptr)
    {
        handle_log("Url %s found in local cache.", url.c_str());
        return cache_dto->to_query_string();
    }

    handle_log("Url %s does not exist in local cache.", url.c_str());
    auto external_cache_dto = repository->find_by_value("url", url);

    if(external_cache_dto == nullptr)
        throw std::runtime_error("Cache item " + url + " does not exist in the network.");
    delete repository;

    auto client = new Client(external_cache_dto->port);
    auto communication = TcpCommunication(client->get_connection());

    std::string request = std::string(StandardCommunication::Search) + url;

    handle_logB("Writing request to node %d: %s", external_cache_dto->port, request.c_str());
    communication.write_message(request);

    std::string response = communication.read_message();
    handle_logB("Reading response from node %d: %s", external_cache_dto->port, response.c_str());

    auto new_cache_item = CacheUpsertDto(response);
    new_cache_item.port = DatabaseContext::port;

    repository = new CacheRepository();
    repository->insert(new_cache_item);
    delete repository;

    auto *delivery_network = DeliveryNetwork::get_instance();
    std::string command_nodes = StandardCommunication::NewDuplicate +
                                ExternalCache(new_cache_item).to_query_string();
    delivery_network->publish_new_information(command_nodes);

    return response;
}

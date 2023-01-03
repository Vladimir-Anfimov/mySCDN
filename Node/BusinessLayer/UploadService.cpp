#include "UploadService.h"
#include "../Infrastructure/DeliveryNetwork.h"

UploadService::UploadService() {}

void UploadService::upload_cache_item(const std::string& command) {
    auto upload_object = CacheUpsertDto(command);
    auto *repository = new CacheRepository();
    repository->remove("url", upload_object.url);
    repository->insert(upload_object);
    delete repository;

    auto external_cache = ExternalCache(upload_object);
    auto command_nodes = std::string(StandardCommunication::PurgeAndInform) + external_cache.to_query_string();

    auto *delivery_network = DeliveryNetwork::get_instance();
    delivery_network->publish_new_information(command_nodes);
}

void UploadService::purge_and_update_external_cache(const std::string& command) {
    auto external_cache = ExternalCache(command);
    CacheUpsertDto upsert_cache = CacheUpsertDto(external_cache);

    auto *repository = new CacheRepository();
    repository->remove("url", external_cache.url);
    repository->insert(upsert_cache);
    delete repository;
}

std::string UploadService::initialise_external_node() {
    std::string response = "";
    auto repository = new CacheRepository();
    std::vector<ExternalCache> entire_cache = repository->select_all();
    for(const auto& item : entire_cache)
    {
        response += item.to_query_string() + std::string(StandardCommunication::Splitter);
    }
    return response;
}

#include "InitialiseService.h"
#include "../DTO/ExternalCache.h"
#include "../DataLayer/CacheRepository.h"

InitialiseService::InitialiseService(int origin_port): origin_port(origin_port) {}

void InitialiseService::initialise() {
    try{
        auto client = new Client(origin_port);
        auto communication = TcpCommunication(client->get_connection());
        communication.write_message(std::string(StandardCommunication::Initialise));
        std::string response = communication.read_message();
        handle_log("Origin port %d responded with %s", origin_port, response.c_str());
        add_to_database(response);
    }
    catch (std::exception& exp)
    {
        handle_error("Trying to initialise database from origin port %d has failed: %s",
                     origin_port, exp.what());
    }
}

void InitialiseService::add_to_database(const std::string& response) {
    auto delimiter = std::string(StandardCommunication::Splitter);
    std::vector<ExternalCache> external_cache;

    std::size_t start = 0;
    std::size_t last;
    while((last = response.find(delimiter, start)) != std::string::npos)
    {
        std::string cache_query = response.substr(start, last - start);
        external_cache.emplace_back(cache_query);
        start = last + delimiter.size();
    }

    auto repository = CacheRepository();
    for(const auto& cache_item : external_cache)
    {
        repository.insert(CacheUpsertDto(cache_item));
    }
}

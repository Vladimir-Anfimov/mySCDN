#include "ExternalCache.h"

ExternalCache::ExternalCache(const std::string& query_string)
{
    auto mapper = Mapper(query_string);
    url = mapper.map( "url");
    available_until = stoi(mapper.map("available_until"));
    port = stoi(mapper.map("port"));
}

ExternalCache::ExternalCache(const CacheUpsertDto& cache_upsert)
{
    this->url = cache_upsert.url;
    this->port = cache_upsert.port;
    this->available_until = cache_upsert.available_until;
}

std::string ExternalCache::to_query_string() const
{
    return std::string(
            "url="+ url+
            "&available_until="+ std::to_string(available_until)+
            "&port=" + std::to_string(port)
    );
}

ExternalCache::ExternalCache(const char url[], int available_until, int port) {
    this->url = std::string(url);
    this->available_until = available_until;
    this->port = port;
}

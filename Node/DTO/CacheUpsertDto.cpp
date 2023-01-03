#include "./CacheUpsertDto.h"

CacheUpsertDto::CacheUpsertDto(const std::string& query_string)
{
    auto mapper = Mapper(query_string);
    url = mapper.map( "url");
    content = mapper.map( "content");
    available_until = stoi(mapper.map("available_until"));
    port = stoi(mapper.map("port"));
}

CacheUpsertDto::CacheUpsertDto(const ExternalCache& external_cache)
{
    url = external_cache.url;
    content = "";
    available_until = external_cache.available_until;
    port = external_cache.port;
}

std::string CacheUpsertDto::to_query_string() const
{
    return std::string(
            "url="+ url+
            "&content="+ content+
            "&available_until="+ std::to_string(available_until)+
            "&port=" + std::to_string(port)
    );
}
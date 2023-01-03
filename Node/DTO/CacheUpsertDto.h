#pragma once
#include <string>
#include "Mapper.h"
#include "./ExternalCache.h"

struct ExternalCache;

struct CacheUpsertDto {
    std::string url;
    std::string content;
    int available_until;
    int port;

    explicit CacheUpsertDto(const std::string& query_string);

    explicit CacheUpsertDto(const ExternalCache& external_cache);

    std::string to_query_string() const;
};
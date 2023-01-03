#pragma once
#include <string>
#include "Mapper.h"
#include "./CacheUpsertDto.h"

struct CacheUpsertDto;

struct ExternalCache {
    std::string url;
    int available_until;
    int port;

    explicit ExternalCache(const std::string& query_string);

    explicit ExternalCache(const char url[], int available_until, int port);

    explicit ExternalCache(const CacheUpsertDto& cache_upsert);

    std::string to_query_string() const;
};
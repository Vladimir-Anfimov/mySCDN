#pragma once

#include <string>
#include "Mapper.h"
#include "ExternalCache.h"


struct CacheDto {
    int id;
    std::string url;
    std::string content;
    int available_until;
    int port;

    explicit CacheDto(const std::string& query_string);


    explicit CacheDto(int id, const char url[], const char content[], int available_until, int port);

    std::string to_query_string();
};
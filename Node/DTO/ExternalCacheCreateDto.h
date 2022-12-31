#pragma once
#include <string>
#include "../Common/Mapper.h"

struct ExternalCacheCreateDto {
    std::string url;
    std::string content;
    int available_until;
    int port;

    explicit ExternalCacheCreateDto(const std::string& query_string)
    {
        auto mapper = Mapper(query_string);
        url = mapper.map( "url");
        content = mapper.map( "content");
        available_until = stoi(mapper.map("available_until"));
        port = stoi(mapper.map("port"));
    }
};
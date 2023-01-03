#pragma once

#include <string>
#include <Mapper.h>

struct CacheUploadRequest {
    std::string url;
    std::string content;
    int ttl;
    int port;

    explicit CacheUploadRequest(std::string query_string)
    {
        auto mapper = Mapper(query_string);
        url = mapper.map( "url");
        content = mapper.map( "content");
        ttl = stoi(mapper.map("ttl"));
        port = stoi(mapper.map("port"));
    }
};
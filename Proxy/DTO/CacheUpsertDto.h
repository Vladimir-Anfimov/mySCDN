#pragma once
#include <string>
#include "Mapper.h"
#include "CacheUploadRequest.h"

struct CacheUpsertDto {
    std::string url;
    std::string content;
    int available_until;
    int port;

    CacheUpsertDto(const std::string& query_string)
    {
        auto mapper = Mapper(query_string);
        url = mapper.map( "url");
        content = mapper.map( "content");
        available_until = stoi(mapper.map("available_until"));
        port = stoi(mapper.map("port"));
    }

    CacheUpsertDto(const CacheUploadRequest& upload_request)
    {
        url = upload_request.url;
        content = upload_request.content;
        available_until = upload_request.ttl + time(nullptr);
        port = upload_request.port;
    }

    std::string to_query_string() const
    {
        return std::string(
                "url="+ url+
                "&content="+ content+
                "&available_until="+ std::to_string(available_until)+
                "&port=" + std::to_string(port)
        );
    }
};
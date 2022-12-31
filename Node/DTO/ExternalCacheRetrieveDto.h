#pragma once

#include <string>
#include "../Common/Mapper.h"

struct ExternalCacheRetrieveDto {
    int id;
    std::string url;
    std::string content;
    int available_until;
    int port;

    ExternalCacheRetrieveDto(const std::string& query_string)
    {
        auto mapper = Mapper(query_string);

        id = stoi(mapper.map( "id"));
        url = mapper.map( "url");
        content = mapper.map( "content");
        available_until = stoi(mapper.map("available_until"));
        port = stoi(mapper.map("port"));
    }

    ExternalCacheRetrieveDto(int id, const char url[], const char content[], int available_until, int port)
    {
        this->id = id;
        this->url = std::string(url);
        this->content = std::string(content);
        this->available_until = available_until;
        this->port = port;
    }

    std::string to_query_string()
    {
        return std::string(
                "id="+std::to_string(id)+
                "&available_until="+ std::to_string(available_until)+
                "&url="+ url+
                "&content="+ content+
                "&port=" + std::to_string(port)
        );
    }
};
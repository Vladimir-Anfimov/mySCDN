#include <iostream>
#include "Infrastructure/TcpServer.h"
#include "DataLayer/CacheRepository.h"
#include "DTO/CacheRetrieveDto.h"
#include "DTO/ExternalCacheCreateDto.h"
#include "DataLayer/ExternalCacheRepository.h"

int main(int argc, char* argv[]) {
//    auto server = new TcpServer(9995);
//    server->start_listening();
//    auto obj = CacheCreateDto("url=america&content=america e mica&available_until=69696");
////
//    auto repo = CacheRepository();
//    repo.insert(obj);
//    std::string x = "america";
//    auto result = repo.find_by_value("id", 2);
//    std::cout<<result->to_query_string();
//    repo.remove<std::string>("url", "america");

    auto obj = ExternalCacheCreateDto("url=america&content=america e mica&available_until=69696&port=22");

    auto repo = ExternalCacheRepository();
    repo.insert(obj);
    std::string x = "america";
    auto result = repo.find_by_value("id", 2);
    std::cout<<result->to_query_string();
}
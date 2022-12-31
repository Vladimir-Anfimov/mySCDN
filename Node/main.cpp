#include <iostream>
#include "DTO/CacheUpsertDto.h"
#include "DataLayer/CacheRepository.h"

int main(int argc, char* argv[]) {

    auto obj = CacheUpsertDto(
            "url=germania&content=germania e cool&available_until=69696&port=22");

    auto repo = CacheRepository();

//    repo.insert(obj);
    auto result = repo.find_by_value("port", 22);
    std::cout<<result->to_query_string();
}
#include "SearchService.h"
#include "../DataLayer/CacheRepository.h"
#include "../Common/Command.h"

SearchService::SearchService() {}

std::string SearchService::find_content(const std::string &command) {
    std::string url = Command::get_url_from_search_command(command);
    auto *repository = new CacheRepository();

    auto cache_dto = repository->find_by_value("url", url);
    if(cache_dto == nullptr)
        throw std::runtime_error("Url " + url + " does not exist in local cache.");
    return cache_dto->content;
}

#pragma once
#include "../DTO/CacheUpsertDto.h"
#include "../DTO/ExternalCache.h"
#include "../DataLayer/CacheRepository.h"
#include "StandardCommunication.h"


class UploadService {
public:
    explicit UploadService();
    void upload_cache_item(const std::string& command);
    void purge_and_update_external_cache(const std::string& command);
    std::string initialise_external_node();
};

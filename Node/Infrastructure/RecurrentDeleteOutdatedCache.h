#pragma once

#include <Print.h>
#include <thread>
#include "../DataLayer/CacheRepository.h"

using namespace Utils::Print;

void recurrent_delete_outdated_cache()
{
    constexpr int interval_seconds = 3;
    std::thread([interval_seconds]{
        while(true)
        {
            try {
                auto repository = new CacheRepository();
                repository->remove("available_until", time(nullptr), "<");
            }
            catch (std::exception& ex)
            {
                handle_warning("Failed to remove outdated cache.");
            }
            std::this_thread::sleep_for(std::chrono::seconds (interval_seconds));
        }
    }).detach();
}
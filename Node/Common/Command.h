#pragma once
#include "StandardCommunication.h"
#include <string>
#include "../DTO/CacheUpsertDto.h"
#include <cstring>

class Command {
    static bool starts_with(const std::string& haystack, const std::string &needle)
    {
        if(needle.size() > haystack.size())
            return false;
        for(int i=0;i<needle.size();i++)
            if(needle[i] != haystack[i])
                return false;
        return true;
    }

public:
    static bool is_search(const std::string& command)
    {
        return starts_with(command, StandardCommunication::Search);
    }
    static std::string get_url_from_search_command(const std::string& command)
    {
        std::string url;
        for(int i = strlen(StandardCommunication::Search); i< command.size();i++)
            url.push_back(command[i]);
        return url;
    }

    static bool is_upload(const std::string& command)
    {
        return starts_with(command, StandardCommunication::Upload);
    }

    static bool is_purge_and_inform(const std::string& command)
    {
        return starts_with(command, StandardCommunication::PurgeAndInform);
    }

    static bool is_initialise(const std::string& command)
    {
        return starts_with(command, StandardCommunication::Initialise);
    }
};


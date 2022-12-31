#pragma once
#include "StandardCommunication.h"
#include <string>

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
    static bool is_upload(const std::string& command)
    {
        return starts_with(command, StandardCommunication::Upload);
    }
};


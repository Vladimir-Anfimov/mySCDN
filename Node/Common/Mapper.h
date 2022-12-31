#pragma once

#include <string>
#include <stdexcept>

class Mapper
{
    std::string query_string;
public:
    Mapper(const std::string& params_list)
    {
        query_string = params_list;
    };

    std::string map(const std::string& param_name)
    {
        std::string value = "";
        std::size_t index = query_string.find(param_name + "=");
        if(index == std::string::npos)
            throw std::runtime_error("Param " + param_name + " could not be found in query string " + query_string);

        index += param_name.size() + 1;
        for(;index < query_string.size() && query_string[index] != '&'; index++)
            value.push_back(query_string[index]);

        return value;
    }
};
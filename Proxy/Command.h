#pragma once

#include <string>
#include <StandardCommunication.h>
#include <cstring>

class Command
{
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
    static bool is_ping(const std::string& command)
    {
        return starts_with(command, StandardCommunication::Ping);
    }
    static int get_port_from_command(const std::string& command)
    {
        std::string port = "";
        for(int i=strlen(StandardCommunication::Ping);i<command.size();i++)
        {
            if(!isdigit(command[i]))
                throw std::runtime_error("Command " + command + " does not have a valid port.");
            port.push_back(command[i]);
        }
        return stoi(port);
    }

};


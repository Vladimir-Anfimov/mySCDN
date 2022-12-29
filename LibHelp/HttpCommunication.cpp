#include <string>
#include <regex>
#include <iostream>
#include "HttpCommunication.h"
#include "Print.h"

using namespace Utils::Print;

HttpCommunication::HttpCommunication(int client): TcpCommunication(client){
    write_pattern = HTTP_HEADER_PATTERN_WRITE;
}

std::string HttpCommunication::read_message() const {
    std::string message = TcpCommunication::read_message();
    return extract_content(message);
}

std::string HttpCommunication::extract_content(const std::string &message) const {
    std::string content = "";
    std::size_t index = message.find("GET /");
    if(index == std::string::npos)
        throw std::runtime_error("Request path is not correctly formulated.");
    index += 5;
    for(;index<message.size();index++)
    {
        if(message[index] == ' ')
            break;
        else
            content.push_back(message[index]);
    }
    return content;
}

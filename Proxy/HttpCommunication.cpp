#include <string>
#include <regex>
#include <iostream>
#include <unistd.h>
#include "HttpCommunication.h"
#include "Print.h"

using namespace Utils::Print;

HttpCommunication::HttpCommunication(int client):client(client){}

std::string HttpCommunication::read_message() const {
    char message[MESSAGE_MAX_BUFFER_SIZE];
    if(read(client, &message, MESSAGE_MAX_BUFFER_SIZE) < 0)
        throw std::runtime_error("Message could not be read.");

    if(strlen(message) > MESSAGE_MAX_BUFFER_SIZE)
        throw std::runtime_error("Message size exceeded the limit");

    return extract_content(message);
}

void HttpCommunication::write_message(const std::string &message) const {
    char response[MESSAGE_MAX_BUFFER_SIZE];

    sprintf(response, HTTP_HEADER_PATTERN_WRITE, message.size()+1, message.c_str());

    if(write(client, response, strlen(response) + 1) < 0)
        throw std::runtime_error("Failed to write message back to client");
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

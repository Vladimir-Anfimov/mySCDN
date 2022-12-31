#include <string>
#include <regex>
#include <iostream>
#include <unistd.h>
#include "HttpCommunication.h"
#include "Print.h"

using namespace Utils::Print;

HttpCommunication::HttpCommunication(int client): TcpCommunication(client){
}

std::string HttpCommunication::read_message() const {
    std::string message = TcpCommunication::read_message();
    return extract_content(message);
}

std::string HttpCommunication::extract_content(const std::string &message) const {
    std::string content = "";
    if(!is_http_message(message)) {
        throw std::runtime_error("Request path is not correctly formulated for a HTTP request.");
    }
    std::size_t index = 5;
    for(;index<message.size();index++)
    {
        if(message[index] == ' ')
            break;
        else
            content.push_back(message[index]);
    }
    return content;
}

void HttpCommunication::write_message(const std::string &message) const {
    char response[MESSAGE_MAX_BUFFER_SIZE];
    sprintf(response, HTTP_HEADER_PATTERN_WRITE, message.size()+1, message.c_str());

    if(write(client, response, strlen(response) + 1) < 0)
        throw std::runtime_error("Failed to write message back to client");
}

bool HttpCommunication::is_http_message(const std::string &message) {
    std::size_t index = message.find("GET /");
    return index == 0;
}


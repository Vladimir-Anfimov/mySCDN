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
        throw std::runtime_error("Message was could not be read.");

    if(strlen(message) > MESSAGE_MAX_BUFFER_SIZE)
        throw std::runtime_error("Message size is exceeded the limit");

    return message;
}

void HttpCommunication::write_message(const char message[]) const {
    char response[MESSAGE_MAX_BUFFER_SIZE];

    sprintf(response, HTTP_HEADER_PATTERN_WRITE, strlen(message)+1, message);

    if(write(client, response, strlen(response) + 1) < 0)
        throw std::runtime_error("Failed to write message back to client");
}

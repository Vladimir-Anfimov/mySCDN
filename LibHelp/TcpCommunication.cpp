#include "TcpCommunication.h"
#include <string>
#include <regex>
#include <iostream>
#include <unistd.h>
#include "HttpCommunication.h"
#include "Print.h"

using namespace Utils::Print;

TcpCommunication::TcpCommunication(int client):client(client){}

std::string TcpCommunication::read_message() const {
    char message[MESSAGE_MAX_BUFFER_SIZE];
    if(read(client, &message, MESSAGE_MAX_BUFFER_SIZE) < 0)
        throw std::runtime_error("Message could not be read.");

    if(strlen(message) > MESSAGE_MAX_BUFFER_SIZE)
        throw std::runtime_error("Message size exceeded the limit");

    return message;
}

void TcpCommunication::write_message(const std::string &message) const {
    if(message.size() > MESSAGE_MAX_BUFFER_SIZE)
        throw std::runtime_error("The message that has to be returned from the server is too long.");

    if(write(client, message.c_str(), message.size() + 1) < 0)
        throw std::runtime_error("Failed to write message back to client");
}


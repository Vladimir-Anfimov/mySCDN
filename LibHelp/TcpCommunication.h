#pragma once

#include <string>

class TcpCommunication {
protected:
    int client;
    constexpr static int MESSAGE_MAX_BUFFER_SIZE = 2048;
public:
    explicit TcpCommunication(int client);
    virtual std::string read_message() const;
    virtual void write_message(const std::string& message) const;
};
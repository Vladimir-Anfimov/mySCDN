#pragma once
#include "TcpCommunication.h"

class HttpCommunication: public TcpCommunication {
private:constexpr static char HTTP_HEADER_PATTERN_WRITE[] =
            "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: %lu\n\n%s";
private:
    std::string extract_content(const std::string& message) const;
public:
    explicit HttpCommunication(int client);
    std::string read_message() const override;
};
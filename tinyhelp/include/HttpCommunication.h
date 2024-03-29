#pragma once
#include "TcpCommunication.h"

class HttpCommunication: public TcpCommunication {
private:constexpr static char HTTP_HEADER_PATTERN_WRITE[] =
            "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: %lu\n\n%s";
private:
public:
    static std::string extract_content(const std::string& message);
    explicit HttpCommunication(int client);
    std::string read_message() const override;
    void write_message(const std::string& message) const override;

    bool static is_http_message(const std::string& message);
};
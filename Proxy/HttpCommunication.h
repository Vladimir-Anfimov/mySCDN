#pragma once

class HttpCommunication {
private:
    int client;
    constexpr static int MESSAGE_MAX_BUFFER_SIZE = 2048;
    constexpr static char HTTP_HEADER_PATTERN_WRITE[] =
            "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: %d\n\n%s";
private:
    std::string extract_content(const std::string& message) const;
public:
    explicit HttpCommunication(int client);
    std::string read_message() const;
    void write_message(const std::string& message) const;
};
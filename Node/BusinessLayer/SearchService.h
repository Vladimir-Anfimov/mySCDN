#pragma once
#include <string>

class SearchService {
public:
    explicit SearchService();
    std::string find_content(const std::string &command);
};
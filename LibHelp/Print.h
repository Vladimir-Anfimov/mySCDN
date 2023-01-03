#pragma once
#include <cstdarg>

namespace Utils::Print
{
    void handle_print(const char* print_type, const char *format, va_list args);
    void handle_error(const char *msg, ...);
    void handle_warning(const char *msg, ...);
    void handle_log(const char *msg, ...);
    void handle_logG(const char *msg, ...);
    void handle_logR(const char *msg, ...);
    void handle_logB(const char *msg, ...);

}
#include <cstdio>
#include <cstdlib>
#include <cerrno>
#include <cstring>
#include "Print.h"
#include <string>
#include <chrono>
#include <iomanip>
#include <iostream>

namespace Utils::Print {
    void handle_print(const char *print_type, const char *format, va_list args) {
        std::time_t t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        std::tm time_formatted;
        localtime_r(&t, &time_formatted);
        std::cout << std::put_time(&time_formatted, "%H:%M:%S") << " ";

        printf("%s: ", print_type);
        vprintf(format, args);
        printf("\n");
    }

    void handle_error(const char *msg, ...) {
        va_list args;
        va_start(args, msg);
        handle_print("ERROR", msg, args);
        va_end(args);
        char *error_msg = strerror(errno);
        printf("STRERROR: %s \n", error_msg);
        exit(EXIT_FAILURE);
    }

    void handle_log(const char *msg, ...) {
        va_list args;
        va_start(args, msg);
        handle_print("LOG", msg, args);
        va_end(args);
    }

    void handle_warning(const char *msg, ...) {
        va_list args;
        va_start(args, msg);
        handle_print("WARNING", msg, args);
        va_end(args);
    }

    void handle_logG(const char *msg, ...) {
        va_list args;
        printf("\033[0;32m");
        va_start(args, msg);
        handle_print("LOG", msg, args);
        va_end(args);
        printf("\033[0;38m");
    }

    void handle_logR(const char *msg, ...) {
        va_list args;
        printf("\033[0;31m");
        va_start(args, msg);
        handle_print("LOG", msg, args);
        va_end(args);
        printf("\033[0;38m");
    }

    void handle_logB(const char *msg, ...)
    {
        va_list args;
        printf("\033[0;34m");
        va_start(args, msg);
        handle_print("LOG", msg, args);
        va_end(args);
        printf("\033[0;38m");
    }

}


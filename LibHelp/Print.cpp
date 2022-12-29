#include <cstdio>
#include <cstdlib>
#include <cerrno>
#include <cstring>
#include "Print.h"

namespace Utils::Print {
    void handle_print(const char *print_type, const char *format, va_list args) {
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
}


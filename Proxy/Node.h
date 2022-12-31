#pragma once
#include <time.h>

struct Node {
    int port;
    time_t last_ping;

    Node(int port, time_t last_ping): port(port), last_ping(last_ping){}
};
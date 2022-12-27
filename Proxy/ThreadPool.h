#pragma once
#include <vector>
#include <thread>
#include <functional>
#include <queue>

class ThreadPool {
    bool terminate = false;
    std::vector<std::thread> threads;
    std::queue<std::function<void()>> jobs;
public:
    explicit ThreadPool(const std::function<void()>& job);
    void Stop();
};



#include "ThreadPool.h"

ThreadPool::ThreadPool(const std::function<void()>& job) {
    auto threads_number = std::thread::hardware_concurrency();
    threads.resize(threads_number);

    for(auto i = 0;i<threads_number;i++)
    {
        std::thread created_thread([job](){
            while(true) job();
        });
        threads.push_back(std::move(created_thread));
    }

    for(auto& created_thread : threads){
       created_thread.join();
    }
}

void ThreadPool::Stop() {
    terminate = false;
}



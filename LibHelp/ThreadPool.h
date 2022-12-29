#pragma once
#include <vector>
#include <thread>
#include <functional>
#include <queue>
#include <condition_variable>

template <typename TData>
class ThreadPool {
protected:
    std::condition_variable data_queue_condition_variable;
    std::vector<std::thread> threads;
    std::mutex data_queue_mutex;
    std::queue<TData> data_queue;
    bool end_execution;
protected:
    virtual void process_event(TData event_data) = 0;
    void execute_work();
    void queue_data(TData data);
public:
    ThreadPool();
    ~ThreadPool();
};

template<typename TData>
ThreadPool<TData>::~ThreadPool() {
    end_execution = true;
    data_queue_condition_variable.notify_all();
    for(auto& thread : threads)
        if(thread.joinable())
            thread.join();
}

template<typename TData>
ThreadPool<TData>::ThreadPool(): end_execution(false) {
    auto threads_number = std::thread::hardware_concurrency();
    if(threads_number == 0)
        threads_number = 1;

    for(int i=0;i<threads_number;i++)
        threads.push_back(std::move(std::thread(&ThreadPool::execute_work, this)));
}

template<typename TData>
void ThreadPool<TData>::queue_data(TData data) {
    std::lock_guard<std::mutex> guard(data_queue_mutex);
    data_queue.push(data);
    data_queue_condition_variable.notify_one();
}

template<typename TData>
void ThreadPool<TData>::execute_work() {
    TData event_data;
    while (!end_execution) {
        std::unique_lock<std::mutex> lock_queue(data_queue_mutex);
        data_queue_condition_variable.wait(lock_queue, [&] {
            return !data_queue.empty() || end_execution;
        });
        if (!data_queue.empty()) {
            event_data = data_queue.front();
            data_queue.pop();
            lock_queue.unlock();
            process_event(event_data);
        } else
            lock_queue.unlock();
    }
}


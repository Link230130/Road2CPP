#pragma once

#include <mutex>
#include <queue>
#include <condition_variable>
#include <vector>
#include <iostream>

template<typename T>
class SafeQueue
{
public:
    SafeQueue() = default;

    ~SafeQueue() = default;

    SafeQueue(const SafeQueue& other) = delete;
    SafeQueue& operator=(const SafeQueue& other) = delete;

    SafeQueue(SafeQueue&& other) = delete;
    SafeQueue(const SafeQueue&& other) = delete;
    SafeQueue& operator=(const SafeQueue&& other) = delete;

    bool empty()
    {
        std::unique_lock<std::mutex> locker(m_mutex);
        return m_queue.empty();
    }

    int size()
    {
        std::unique_lock<std::mutex> locker(m_mutex);
        return m_queue.size();
    }

    void push(T& value)
    {
        std::unique_lock<std::mutex> locker(m_mutex);
        m_queue.emplace(value); // 使用emplace会效率更高
    }

    void push(T&& value)
    {
        std::unique_lock<std::mutex> locker(m_mutex);
        m_queue.emplace(std::move(value));
    }

    bool pop(T& value)
    {
        std::unique_lock<std::mutex> locker(m_mutex);
        if (m_queue.empty())
        {
            return false;
        }
        else
        {
            value = std::move(m_queue.front());
            m_queue.pop();
            return true;
        }
    }

private:
    std::mutex          m_mutex;
    std::queue<T>       m_queue;
};
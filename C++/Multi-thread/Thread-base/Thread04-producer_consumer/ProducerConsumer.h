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
        m_queue.emplace(value); // ʹ��emplace��Ч�ʸ���
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

template<typename T>
class Producer_Consumer
{
public:
    Producer_Consumer()
        : m_nQueueMaxSize(20)
        , m_vecProducerThread(2)
        , m_vecConsumerThread(2)
    {
        intialize();
    }

    Producer_Consumer(int nQueueMaxSize, int nProducerNum, int nConsumerNum)
        : m_nQueueMaxSize(nQueueMaxSize)
        , m_vecProducerThread(nProducerNum)
        , m_vecConsumerThread(nConsumerNum)
    {
        intialize();
    }

    // ����
    ~Producer_Consumer()
    {
        m_bRunning = false;
        m_cvQueueNotEmpty.notify_all();
        m_cvQueueNotFull.notify_all();

        for (auto& t : m_vecProducerThread)
        {
            if (t.joinable())
            {
                t.join();
            }
        }
        for (auto& t : m_vecConsumerThread)
        {
            if (t.joinable())
            {
                t.join();
            }
        }
    }

private:
    void intialize()
    {
        m_bRunning = true;
        m_nProducedNum = -1;

        for (size_t i = 0; i < m_vecProducerThread.size(); i++)
        {
            m_vecProducerThread[i] = std::thread(&Producer_Consumer::producer, this);
        }
        for (size_t i = 0; i < m_vecConsumerThread.size(); i++)
        {
            m_vecConsumerThread[i] = std::thread(&Producer_Consumer::consumer, this);
        }
    }

    bool isFull()
    {
        if (m_queue.size() >= m_nQueueMaxSize)
        {
            return true;
        }
        return false;
    }

    // ������
    void producer()
    {
        while (m_bRunning)
        {
            std::unique_lock<std::mutex> locker(m_mutex);

            if (isFull())
            {
                std::cout << "Thread["<<std::this_thread::get_id()<<"],Queue is full! Waiting for m_cvQueueNotFull\n";
                m_cvQueueNotFull.wait(locker);
            }
            if (!isFull())
            {
                m_nProducedNum++;
                
                // do something
                std::this_thread::sleep_for(std::chrono::microseconds(100));

                m_queue.push(m_nProducedNum);
                // ����һ���������߳�
                m_cvQueueNotEmpty.notify_one();
                if (m_nProducedNum > 1000)
                {
                    m_nProducedNum = 0;
                }
            }
        }
    }

    // ������
    void consumer()
    {
        while (m_bRunning)
        {
            std::unique_lock<std::mutex> locker(m_mutex);
            if (m_queue.empty())
            {
                std::cout << "Thread[" << std::this_thread::get_id() << "],Queue is empty! Waiting for m_cvQueueNotEmpty\n";
                m_cvQueueNotEmpty.wait(locker);
            }
            if (!m_queue.empty())
            {
                T value;
                bool bRet = m_queue.pop(value);
                std::cout << "Thread[" << std::this_thread::get_id() << "],consumer get value = [" << value << "]\n";
                // ����һ���������߳�
                m_cvQueueNotFull.notify_one();
            }
        }
    }

private:
    SafeQueue<T>                m_queue;
    int                         m_nQueueMaxSize;
    std::condition_variable     m_cvQueueNotFull;       // ����δ��
    std::condition_variable     m_cvQueueNotEmpty;      // ���в�Ϊ��

    std::vector<std::thread>    m_vecProducerThread;    // �������߳��б�
    std::vector<std::thread>    m_vecConsumerThread;    // �������߳��б�

    std::mutex                  m_mutex;
    std::atomic<bool>           m_bRunning;             // �߳��������
    std::atomic<int>            m_nProducedNum;         // �������������Ĳ�Ʒ
};
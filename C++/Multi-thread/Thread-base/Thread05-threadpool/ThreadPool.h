#pragma once

#include <functional>
#include <future>
#include <memory>
#include "SafeQueue.h"

class ThreadPool
{
public:
    ThreadPool()
        : m_vecThread(std::thread::hardware_concurrency())
        , m_bRunning(true)
    {
        initialize();
    }

    ThreadPool(int nThreadNum)
        : m_vecThread(nThreadNum)
        , m_bRunning(true)
    {
        initialize();
    }

    ~ThreadPool()
    {
        m_bRunning = false;
        m_cv.notify_all();
        for (auto& t : m_vecThread)
        {
            if (t.joinable())
            {
                t.join();
            }
        }
    }

    ThreadPool(const ThreadPool&) = delete;
    ThreadPool& operator=(const ThreadPool&) = delete;
    ThreadPool(const ThreadPool&&) = delete;
    ThreadPool& operator=(const ThreadPool&&) = delete;

    template<typename Func, typename... Args>
    auto submitTask(Func&& func, Args ... args)
    {
        // 1.获取函数的返回值类型（std::invoke_result是C++17标准, std::result_of是C++11标准）
        //using returnType = typename std::invoke_result<Func, Args ...>::type;
        using returnType = typename std::result_of<Func(Args...)>::type;
        
        // 2.将任意可调用对象包装成不带有参数列表的可调用对象，使用std::forward是为了保持语义（在这一步骤中去掉了参数列表）
        std::function<returnType()> taskFun1 = std::bind(std::forward<Func>(func), std::forward<Args>(args)...);

        // 3.将可调用对象包装成packaged_task，便于获取返回值（将可调用对象的返回值包装成future）
        auto taskFun2 = std::make_shared<std::packaged_task<returnType()>>(taskFun1);
        // 4.将打包好的packaged_task封装到一个没有返回值，没有参数列表的匿名函数中，并添加到任务列表（在这一步骤中去掉了返回值）
        TaskType taskFun3 = [taskFun2]() {
            (*taskFun2)();
        };

        // 5.将包装好的任务添加到任务列表并随机唤醒一个线程进行处理
        m_TaskQueue.push(taskFun3);
        m_cv.notify_one();

        // 6.返回任务处理的结果
        return taskFun2->get_future();
    }

private:
    void initialize()
    {
        for (int i = 0; i < m_vecThread.size(); i++)
        {
            auto worker = [=]() {
                while (m_bRunning)
                {
                    TaskType task;
                    bool isSuccess = false;
                    {
                        std::unique_lock<std::mutex> locker(m_mutex);
                        if (this->m_TaskQueue.empty())
                        {
                            this->m_cv.wait(locker);
                        }
                        // 从任务队列中取出一个任务
                        isSuccess = this->m_TaskQueue.pop(task);
                    }
                    if (isSuccess)
                    {
                        //std::cout << "thread[" << std::this_thread::get_id() << "] start running task in worker[" << i << "]";
                        // 执行取出的任务
                        task();
                        //std::cout << "thread[" << std::this_thread::get_id() << "] end running task in worker[" << i << "]";
                    }
                }
            };
            m_vecThread[i] = std::thread(worker);
        }
    }

private:
    using TaskType = std::function<void()>; // 提交到线程池的任务类型，即返回值为void，参数列表为空

    SafeQueue<TaskType>             m_TaskQueue;    // 任务队列
    std::vector<std::thread>        m_vecThread;    // 线程队列
    std::condition_variable         m_cv;           // 条件变量
    std::mutex                      m_mutex;        // 互斥锁

    std::atomic<bool>               m_bRunning;     // 线程池的运行状态
};
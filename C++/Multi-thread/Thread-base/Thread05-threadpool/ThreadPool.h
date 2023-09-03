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
        // 1.��ȡ�����ķ���ֵ���ͣ�std::invoke_result��C++17��׼, std::result_of��C++11��׼��
        //using returnType = typename std::invoke_result<Func, Args ...>::type;
        using returnType = typename std::result_of<Func(Args...)>::type;
        
        // 2.������ɵ��ö����װ�ɲ����в����б�Ŀɵ��ö���ʹ��std::forward��Ϊ�˱������壨����һ������ȥ���˲����б�
        std::function<returnType()> taskFun1 = std::bind(std::forward<Func>(func), std::forward<Args>(args)...);

        // 3.���ɵ��ö����װ��packaged_task�����ڻ�ȡ����ֵ�����ɵ��ö���ķ���ֵ��װ��future��
        auto taskFun2 = std::make_shared<std::packaged_task<returnType()>>(taskFun1);
        // 4.������õ�packaged_task��װ��һ��û�з���ֵ��û�в����б�����������У�����ӵ������б�����һ������ȥ���˷���ֵ��
        TaskType taskFun3 = [taskFun2]() {
            (*taskFun2)();
        };

        // 5.����װ�õ�������ӵ������б��������һ���߳̽��д���
        m_TaskQueue.push(taskFun3);
        m_cv.notify_one();

        // 6.����������Ľ��
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
                        // �����������ȡ��һ������
                        isSuccess = this->m_TaskQueue.pop(task);
                    }
                    if (isSuccess)
                    {
                        //std::cout << "thread[" << std::this_thread::get_id() << "] start running task in worker[" << i << "]";
                        // ִ��ȡ��������
                        task();
                        //std::cout << "thread[" << std::this_thread::get_id() << "] end running task in worker[" << i << "]";
                    }
                }
            };
            m_vecThread[i] = std::thread(worker);
        }
    }

private:
    using TaskType = std::function<void()>; // �ύ���̳߳ص��������ͣ�������ֵΪvoid�������б�Ϊ��

    SafeQueue<TaskType>             m_TaskQueue;    // �������
    std::vector<std::thread>        m_vecThread;    // �̶߳���
    std::condition_variable         m_cv;           // ��������
    std::mutex                      m_mutex;        // ������

    std::atomic<bool>               m_bRunning;     // �̳߳ص�����״̬
};
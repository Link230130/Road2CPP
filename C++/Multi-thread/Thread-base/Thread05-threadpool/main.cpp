#include <iostream>

#include "ThreadPool.h"

using namespace std;

int fun1(int nA, int nB)
{
    // 模拟函数执行的过程
    // do something
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    return nA + nB;
}

void testPool()
{
    auto start = std::chrono::steady_clock::now();
    ThreadPool threadPool;
    int taskNum = 30;
    std::vector<std::future<int>> vecResult(taskNum);

    for (int i = 0; i < taskNum; i++)
    {
        vecResult[i] = threadPool.submitTask(fun1, i, i * i);
    }

    for (int i = 0; i < taskNum; i++)
    {
        std::cout << "result[" << i << "]= " << vecResult[i].get() << "\n";
    }
    auto end = std::chrono::steady_clock::now();
    cout << "使用线程池执行任务共耗时[" << std::chrono::duration<double, std::milli>(end - start).count() << "]毫秒\n";
}

void testNormal()
{
    auto start = std::chrono::steady_clock::now();
    int taskNum = 30;
    std::vector<int> vecResult(taskNum);

    for (int i = 0; i < taskNum; i++)
    {
        vecResult[i] = fun1(i, i * i);
    }

    for (int i = 0; i < taskNum; i++)
    {
        std::cout << "result[" << i << "]= " << vecResult[i] << "\n";
    }
    auto end = std::chrono::steady_clock::now();
    cout << "未使用线程池执行任务共耗时[" << std::chrono::duration<double, std::milli>(end - start).count() << "]毫秒\n";
}

int main()
{
    testPool();
    testNormal();

    return 0;
}
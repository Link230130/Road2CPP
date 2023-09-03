#include <iostream>

#include "ThreadPool.h"

using namespace std;

int fun1(int nA, int nB)
{
    // ģ�⺯��ִ�еĹ���
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
    cout << "ʹ���̳߳�ִ�����񹲺�ʱ[" << std::chrono::duration<double, std::milli>(end - start).count() << "]����\n";
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
    cout << "δʹ���̳߳�ִ�����񹲺�ʱ[" << std::chrono::duration<double, std::milli>(end - start).count() << "]����\n";
}

int main()
{
    testPool();
    testNormal();

    return 0;
}
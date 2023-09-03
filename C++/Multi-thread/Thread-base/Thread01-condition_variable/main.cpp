#include <iostream>
#include <deque>
#include <mutex>
#include <thread>

using namespace std;

std::deque<int> q;          // 队列
std::mutex mtx;             // 互斥锁
std::condition_variable cv; //条件变量

// 生产者
void producer()
{
    int i = 0;

    while (true)
    {
        std::unique_lock<mutex> lock(mtx);
        q.push_back(i);

        // 休眠十毫秒，模拟数据处理过程
        this_thread::sleep_for(std::chrono::milliseconds(10));

        // 唤醒一个线程
        cv.notify_one();

        // 更新i
        i < 999 ? i++ : i = 0;
    }
}


// 消费者
void consumer()
{
    int data = -1;
    while (true)
    {
        std::unique_lock<std::mutex> lock(mtx);
        while (q.empty())
        {
            cv.wait(lock);
        }

        // 从队列中取出一个数据
        data = q.front();
        q.pop_front();

        cout << "thread: [" << this_thread::get_id() << "], Get value from deque is [" << data << "]\n";
    }
}

int main()
{
    thread t1(producer);
    thread t2(consumer);
    thread t3(consumer);

    t1.join();
    t2.join();
    t3.join();
    return 0;
}
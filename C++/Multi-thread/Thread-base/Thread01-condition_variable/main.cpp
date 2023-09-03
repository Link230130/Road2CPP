#include <iostream>
#include <deque>
#include <mutex>
#include <thread>

using namespace std;

std::deque<int> q;          // ����
std::mutex mtx;             // ������
std::condition_variable cv; //��������

// ������
void producer()
{
    int i = 0;

    while (true)
    {
        std::unique_lock<mutex> lock(mtx);
        q.push_back(i);

        // ����ʮ���룬ģ�����ݴ������
        this_thread::sleep_for(std::chrono::milliseconds(10));

        // ����һ���߳�
        cv.notify_one();

        // ����i
        i < 999 ? i++ : i = 0;
    }
}


// ������
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

        // �Ӷ�����ȡ��һ������
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
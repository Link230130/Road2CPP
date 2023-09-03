#include <iostream>
#include <mutex>
#include <thread>
#include <future>
#include <functional>

using namespace std;

int task(int a, int b)
{
    cout << "thread[" << this_thread::get_id() << "] start\n";
    int ret_a = a * a;
    int ret_b = b * 2;

    return ret_a + ret_b;
}

int main()
{
    // launch::async �����߳���ִ��task
    // launch::deferred �ӳٵ��ã�task���������߳���ִ��
    // launch::async | launch::deferred ��async��Ĭ�ϲ��������Զ��ж��Ƿ�Ҫ�����߳���ִ��
    //std::future<int> f = std::async(/*launch::async*/launch::deferred, task, 1, 2);
    //cout << "Thread[" << this_thread::get_id() << "] return value=[" << f.get() << "]\n";

    // �÷�1
    std::packaged_task<int(int, int)> pt(task);
    pt(1,2);
    cout << "Thread[" << this_thread::get_id() << "] return value=[" << pt.get_future().get() << "]\n";

    // �÷�2
    std::function<int()> fn1 = std::bind(task,1,2);
    std::packaged_task<int()> pt1(fn1);
    pt1();
    cout << "Thread[" << this_thread::get_id() << "] return value=[" << pt1.get_future().get() << "]\n";

    return 0;
}
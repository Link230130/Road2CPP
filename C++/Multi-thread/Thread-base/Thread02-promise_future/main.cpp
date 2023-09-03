#include <iostream>
#include <mutex>
#include <thread>
#include <future>

using namespace std;


void task(int a, std::future<int>& b, std::promise<int>& ret)
{
    cout << "thread[" << this_thread::get_id() << "] start\n";
    int ret_a = a * a;

    // 模拟子线程中间有一个耗时操作(这个操作不会使用到参数b)
    this_thread::sleep_for(chrono::microseconds(100));

    int ret_b = b.get() * 2;

    ret.set_value(ret_a + ret_b);
}

int main()
{
    std::promise<int> p_ret;
    std::future<int> f_ret = p_ret.get_future();    // 用于子线程返回结果

    std::promise<int> p_in;
    std::future<int> f_in = p_in.get_future();      //用于子线程获取输入参数

    thread t1(task, 1, std::ref(f_in), std::ref(p_ret));

    // do something
    this_thread::sleep_for(chrono::microseconds(10));
    cout << "thread[" << this_thread::get_id() << "] do something end\n";
    p_in.set_value(2);

    // get()也只能使用一次
    cout << "Thread return value=[" << f_ret.get() << "]\n";

    t1.join();

    return 0;
}
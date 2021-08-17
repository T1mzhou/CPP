#include <chrono>
#include <iostream>

using namespace std;
using namespace std::chrono;

class Timer
{
public:
    Timer() : m_begin(high_resolution_clock::now()) {}

    // 默认输出毫秒
    template<typename Duration=milliseconds>
    int64_t elapsed() const
    {
        return duration_cast<Duration>(high_resolution_clock::now() - m_begin).count();
    }

    // 微妙
    int64_t elapsed_micro() const
    {
        return elapsed<milliseconds>();
    }

    // 纳秒
    int64_t elapsed_nano() const
    {
        return elapsed<nanoseconds>();
    }

    // 秒
    int64_t elapsed_seconds() const
    {
        return elapsed<seconds>();
    }

    // 分
    int64_t elapsed_minutes() const 
    {
        return elapsed<minutes>();
    }

    // 时
    int64_t elapsed_hours() const
    {
        return elapsed<hours>();
    }

private:
    time_point<high_resolution_clock> m_begin;
};

void fun() 
{
    cout << "hello world" << endl;
}

int main() 
{
    Timer t;
    fun();
    cout << t.elapsed() << endl;
    cout << t.elapsed_micro() << endl;
    cout << t.elapsed_nano() << endl;
    cout << t.elapsed_seconds() << endl;
    cout << t.elapsed_minutes() << endl;
    cout << t.elapsed_hours() << endl;
    return 0;
}
#include <thread>
#include <chrono>
#include <iostream>
#include  <thread>

/*
* 测试参数未定义问题
*/

class Sleeper {
public:
    Sleeper(int& i_) : i{ i_ } {};
    void operator()(int k) {
        for (unsigned int j = 0; j <= 5; ++j) {
            std::this_thread::sleep_for(std::chrono::microseconds(100));
            i += k;
        }

        std::cout << std::this_thread::get_id() << std::endl;
    }
private:
    int& i;
};

int main() {
    std::cout << std::endl;

    int valSleeper = 1000;
    std::thread t(Sleeper(valSleeper), 5); // 问题1:同时 读写 valSleeper 问题2:主线程的生命周期可能在子线程执行计算 或者将其ID写入std::cout之前结束;
    //t.detach(); // fact:1000;
    t.join(); // fact:1030;  // 解决生命周期的问题，解决竞态加锁
    std::cout << "valSleeper = " << valSleeper << std::endl; // expected 100 + 6 * 5 = 1030

    std::cout << std::thread::hardware_concurrency() << std::endl; //hhhh果然免费的只有1个线程
}
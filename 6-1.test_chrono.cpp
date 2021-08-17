#include <iostream>
#include <chrono>
#include <ratio>
#include <iomanip> // put_time

int main() {
    std::chrono::milliseconds ms {3}; // 3毫秒
    // 6000微妙
    std::chrono::milliseconds us = 2 * ms;
    // 30Hz clock using fractional ticks
    std::chrono::duration<double, std::ratio<1, 30>> hz30{3.5};  // 1/30秒

    std::cout << "3 ms duration has" << ms.count() << " ticks\n"
    << "6000 us duration has " << us.count() << " ticks\n";

    // 计算时间差
    std::chrono::duration<double, std::ratio<9, 7>> d1(3);
    std::chrono::duration<double, std::ratio<6, 5>> d2(1);
    auto d3 = d1 - d2;
    std::cout << typeid(d3).name() << std::endl;
    std::cout << d3.count() << std::endl;

    // 表示时间点
    using namespace std::chrono;

    using days_type = duration<int, std::ratio<60 * 60 * 24>>;
    time_point<system_clock, days_type> today = time_point_cast<days_type>(system_clock::now());

    std::cout << today.time_since_epoch().count() << " days since epoch " << std::endl;

    // 获取系统时钟的clocks
    system_clock::time_point t1 = system_clock::now();
    std::cout << "Hello World!\n";
    system_clock::time_point t2 = system_clock::now();
    std::cout << (t2 - t1).count() << "tick count" << std::endl;
    // 使用duration_cast将其转换为其他时钟周期的duration
    std::cout << duration_cast<microseconds>(t2 - t1).count() << "tick microseconds" << std::endl;

    // system_clock to_time_t方法可以将一个time_point转换为ctime
    // std::time_t now_c - system_clock::to_time_t(time_point);
    // from_time_t方法相反

    // 格式化时间
    auto t = system_clock::to_time_t(system_clock::now());
    std::cout << std::put_time(std::localtime(&t), "%Y-%m-%d %X") << std::endl;
    std::cout << std::put_time(std::localtime(&t), "%Y-%m-%d %H.%M.%S") << std::endl;
   

    return 0;
}
#include <iostream>
#include <thread>
#include <mutex>

std::once_flag onceFlag;

void do_once() {
    std::call_once(onceFlag, [] { std::cout << "Only once." << std::endl; });
}

void do_once2() {
    std::call_once(onceFlag, [] { std::cout << "Only once2." << std::endl; });
}

int main() {
    std::cout << std::endl;

    std::thread t1(do_once);
    std::thread t2(do_once);
    std::thread t3(do_once2);
    std::thread t4(do_once2);


    t1.join();
    t2.join();
    t3.join();
    t4.join();
}
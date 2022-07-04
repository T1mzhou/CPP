#include <iostream>
#include <string>
#include <mutex>
#include <thread>

std::mutex coutMtx;

thread_local std::string s("hello from ");

void addThreadLocal(std::string const& s2) {
    s += s2;
    std::lock_guard<std::mutex> guard(coutMtx);
    std::cout << s << std::endl;
    std::cout << "&s: " << &s << std::endl;
    std::cout << std::endl;
}

int main() {
    std::cout << std::endl;

    std::thread t1(addThreadLocal, "t1");
    std::thread t2(addThreadLocal, "t2");
    std::thread t3(addThreadLocal, "t3");
    std::thread t4(addThreadLocal, "t4");
    std::thread t5(addThreadLocal, "t5");

    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
}
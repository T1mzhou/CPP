#include <thread>
#include <iostream>
#include <mutex>

int x = 0;
int y = 0;

std::mutex mtx;

void writing() {
    std::lock_guard<std::mutex> guard(mtx);
    x = 2000;
    y = 11;
}

void reading() {
    std::lock_guard<std::mutex> guard(mtx);
    std::cout << "y: " << y << " ";
    std::cout << "x: " << x << std::endl;
}

int main()
{
    std::thread t1(writing);
    std::thread t2(reading);

    t1.join();
    t2.join();
}
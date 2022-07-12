#include <thread>
#include <iostream>
#include <atomic>


std::atomic<int> x{0};
std::atomic<int> y{0};



void writing() {
    x.store(2000);
    y.store(11);
}

void reading() {
    std::cout << "y: " << y.load() << " ";
    std::cout << "x: " << x.load() << std::endl;
}

int main()
{
    std::thread t1(writing);
    std::thread t2(reading);

    t1.join();
    t2.join();
}
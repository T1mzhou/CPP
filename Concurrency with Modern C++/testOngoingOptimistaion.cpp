#include <thread>
#include <iostream>

int x = 0;
int y = 0;

void writing() {
    x = 2000;
    y = 11;
}

void reading() {
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
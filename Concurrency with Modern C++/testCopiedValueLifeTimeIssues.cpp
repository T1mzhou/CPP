#include <iostream>
#include <string>
#include <thread>

void executeTwoThreads() {
    const std::string localString("local string");

    std::thread t1([localString] {
        std::cout << "Per Copy: " << localString << std::endl;
    });

    // life time 
    std::thread t2([&localString] {
        std::cout << "Per Copy: " << localString << std::endl;
    });

    t1.detach();
    t2.detach();
}

using  namespace std::chrono_literals;

int main() {
    std::cout << std::endl;

    executeTwoThreads();

    std::this_thread::sleep_for(1s);

    std::cout << std::endl;
}
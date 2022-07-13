#include <functional>
#include <ios>
#include <iostream>
#include <string>
#include <thread>

using namespace std::chrono_literals;

void byCopy(bool b) {
    std::this_thread::sleep_for(1ms);
    std::cout << "byCopy: " << b << std::endl;
}

void byReference(bool& b) {
    std::this_thread::sleep_for(1ms);
    std::cout << "byReference: " << b << std::endl;
}

void byConstReference(const bool& b) {
    std::this_thread::sleep_for(1ms);
    std::cout << "byConsReference: " << b << std::endl;
}

int main()
{
    std::cout << std::boolalpha << std::endl;

    bool shared(false);

    std::thread t1(byCopy, shared);
    std::thread t2(byReference, std::ref(shared));
    std::thread t3(byConstReference, std::cref(shared));

    shared = false;
    
    t1.join();
    t2.join();
    t3.join();

    std::cout << std::endl;
}
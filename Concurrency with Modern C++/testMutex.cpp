#include <iostream>
#include <mutex>
#include <thread>


std::mutex mtx;


void workOnRes(int i) {
    mtx.lock();

    // shared resource
    std::cout << "hhh " << i << "\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));

    mtx.unlock();
}


int main() {
    std::thread t(workOnRes, 0);
    std::thread t2(workOnRes, 1);

    t.join();
    t2.join();
    return 0;
}

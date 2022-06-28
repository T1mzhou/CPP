#include <chrono>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>
#include <atomic>

std::vector<int> mySharedWork;
//std::mutex mtx;
//std::condition_variable cv;

std::atomic<bool> dataReady{false};

void waitingForWork() {
    std::cout << "Waiting " << std::endl;

    while ( !dataReady.load() ) {
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }

    mySharedWork[1] = 2;
    std::cout << "Work done " << std::endl;
}

void setDataReady() {

    mySharedWork = {1, 0, 3};
    dataReady = true;
    std::cout << "Data prepared" << std::endl;
}

int main()
{
    std::cout << "\n";

    std::thread t1(waitingForWork);
    std::thread t2(setDataReady);

    t1.join();
    t2.join();

    for (auto v : mySharedWork) {
        std::cout << v << " ";
    }
}
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

std::vector<int> mySharedWork;
std::mutex mtx;
std::condition_variable cv;

bool dataReady{false};

void waitingForWork() {
    std::cout << "Waiting " << std::endl;
    std::unique_lock<std::mutex> lck(mtx);
    cv.wait(lck, []{return dataReady;}); // 存在伪唤醒和未唤醒的功能
    mySharedWork[1] = 2;
    std::cout << "Work done " << std::endl;
}

void setDataReady() {

    mySharedWork = {1, 0, 3};

    {
        std::lock_guard<std::mutex> lck(mtx);
        dataReady = true;
    }

    std::cout << "Data prepared" << std::endl;
    cv.notify_one();
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
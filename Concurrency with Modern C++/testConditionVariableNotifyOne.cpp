#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>

std::mutex mtx;
std::condition_variable cv;

bool dataReady{false};

void doTheWork() {
    std::cout << "Processing shared data. " << std::endl;
}

void waitingForWork() {
    std::cout << "Worker: Waiting for work. " << std::endl;
    std::unique_lock<std::mutex> lck(mtx);
    cv.wait(lck, []{return dataReady;}); 
    doTheWork();
    std::cout << "Work done " << std::endl;
}

void setDataReady() {
    {
        std::lock_guard<std::mutex> lck(mtx);
        dataReady = true;
    }

    std::cout << "Sender: Data is ready.\n";
    cv.notify_one();
}

int main()
{
    std::cout << "\n";

    std::thread t1(waitingForWork);
    std::thread t2(setDataReady);

    t1.join();
    t2.join();
}
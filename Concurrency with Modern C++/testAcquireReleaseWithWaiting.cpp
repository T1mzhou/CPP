#include <atomic>
#include <iostream>
#include <thread>
#include <vector>

std::vector<int> mySharedWork;
std::atomic<bool> dataPro(false);

// 顺序上没有 先行关系 
// 线程上有先行关系
void dataProducer() {
    mySharedWork = {1, 0, 3};
    dataPro.store(true, std::memory_order_release);
}

void dataConsumer() {
   // while (!dataPro.load(std::memory_order_acquire));
    dataPro.load(std::memory_order_acquire); // 没有等待生产线程,core dump,因为acq在relese之前，如果不在release之前也会产生未定义的行为可能可以，可能core dump,
    mySharedWork[1] = 2;                     // 取决于 CPU的调度
}

int main() {
    std::cout << std::endl;

    std::thread t2(dataProducer);
    std::thread t1(dataConsumer);
    //std::thread t2(dataProducer);

    t1.join();
    t2.join();

    for (auto  v : mySharedWork) {
        std::cout << v << " ";
    }

    std::cout << "\n\n";
}
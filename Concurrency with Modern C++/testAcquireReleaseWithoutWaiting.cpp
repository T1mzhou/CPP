#include <atomic>
#include <iostream>
#include <thread>
#include <vector>

// 产生未定义的行为,因为mySharedWork存在数据竞争

std::vector<int> mySharedWork;
std::atomic<bool> dataPro(false);

void dataProducer() {
    mySharedWork = {1, 0, 3};
    dataPro.store(true, std::memory_order_release);
}

void dataConsumer() {
   // dataPro.load(std::memory_order_acquire); // 不存在同步关闭
    while (!dataPro.load(std::memory_order_acquire)); // 解决方案
    mySharedWork[1] = 2;
}

int main() {
    std::thread t1(dataConsumer);
    std::thread t2(dataProducer);

    t1.join();
    t2.join();

    for (auto  v : mySharedWork) {
        std::cout << v << " ";
    }

    std::cout << "\n\n";
}
#include <atomic>
#include <iostream>
#include <thread>
#include <vector>

std::vector<int>  mySharedWork;
std::atomic<bool> dataPro(false);
std::atomic<bool> dataCon(false);

void dataProducer() {
    mySharedWork = {1, 0, 3};
    dataPro.store(true, std::memory_order_release);
}

void deliverBoy() {
    while (!dataPro.load(std::memory_order_acquire));
    dataCon.store(true, std::memory_order_release);
}
void dataConsumer() {
    while (!dataCon.load(std::memory_order_acquire));
    mySharedWork[1] = 2;
}

int main() {
    std::cout << std::endl;

    std::thread t1(dataConsumer);
    std::thread t2(deliverBoy);
    std::thread t3(dataProducer);

    t1.join();
    t2.join();
    t3.join();

    for (auto v : mySharedWork) {
        std::cout << v << " ";
    }

    std::cout << "\n\n";
}
#include <vector>
#include <iostream>
#include <thread>
#include <atomic>


std::atomic<int> count = {0};

void add() {
    for (int n = 0; n < 100; ++n) {
        count.fetch_add(1, std::memory_order_relaxed);
    }
}

int main() {
    std::vector<std::thread> v;

    for (int n = 0; n < 10; ++n) {
        v.emplace_back(add); //同步点
    }

    for (auto& t : v) {
        t.join(); // 同步点
    }

    std::cout << "Final Counter value is " << count << '\n'; // count.fetch_add(1, std::memory_order_relaxed);存在先行关系
}
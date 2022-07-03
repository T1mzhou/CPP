#include <atomic>
#include <thread>
#include <iostream>
#include <mutex>

std::atomic<int> atom{0};
int somethingShared{0};

using namespace std::chrono_literals; // Allows integer, floating-point, character, and string literals to produce objects of user-defined type by defining a user-defined suffix.
                                      // https://en.cppreference.com/w/cpp/language/user_literal
                                      // ms：Forms a std::chrono::duration literal representing milliseconds.
void writeShared() {
    somethingShared = 2011;
    atom.store(2, std::memory_order_release);
}

void readShared() {
    while (!(atom.fetch_sub(1, std::memory_order_acquire) > 0)) {
        std::this_thread::sleep_for(100ms);
    }

    std::cout << "somethingShared: " << somethingShared << std::endl;
}

int main() {
    std::cout << std::endl;

    std::thread t1(writeShared);
    std::thread t2(readShared);
    std::thread t3(readShared); // 开启t3后存在数据竞争,因为第二次调用 后美誉哦 对relase进行标记了.book预计是1998，而我的C++17编译器是0，是否编译器 已经修复该问题？
    //std::thread t3(writeShared); // 同时写没有竞态 

    t1.join();
    t2.join();
    t3.join();

    std::cout << "atom: " << atom << std::endl;
    std::cout << std::endl;


}
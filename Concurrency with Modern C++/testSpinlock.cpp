#include <iostream>
#include <atomic>
#include <thread>

class Spinlock{
public:
    void lock() {
        while (flag.test_and_set());
    }

    void unlock() {
        flag.clear();
    }

private:
    std::atomic_flag flag = ATOMIC_FLAG_INIT;
};

Spinlock spin;

void workOnRes(int i) {
    spin.lock();

    // shared resource
    std::cout << "hhh " << i << "\n";

    spin.unlock();
}


int main() {
    std::thread t(workOnRes, 0);
    std::thread t2(workOnRes, 1);

    t.join();
    t2.join();
    return 0;
}

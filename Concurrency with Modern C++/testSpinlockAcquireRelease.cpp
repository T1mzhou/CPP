#include <atomic>
#include <thread>

class Spinlock {
    std::atomic_flag flag;
public:
    Spinlock():flag(ATOMIC_FLAG_INIT) {

    }

    void lock() {
        while (flag.test_and_set(std::memory_order_acquire));
    }

    void unlock() {
        flag.clear(std::memory_order_release);
    }
};

Spinlock spin;

void workOnRes() {
    spin.lock();

    // shared res

    spin.unlock();
}

int main() {
    std::thread t(workOnRes);
    std::thread t2(workOnRes);

    t.join();
    t2.join();
    return 0;
}
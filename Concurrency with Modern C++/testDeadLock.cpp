#include <chrono>
#include <iostream>
#include <memory>
#include <thread>
#include <mutex>


struct CriticalData {
    std::mutex mtx;
};


void deadLock(CriticalData& a, CriticalData& b) {
    a.mtx.lock();

    std::cout << "get the first mutex" << std::endl;
    std::this_thread::sleep_for(std::chrono::microseconds(1));
    b.mtx.lock();
    std::cout << "get the  second mutex" << std::endl;
    // do something with a and b
    a.mtx.unlock();
    b.mtx.unlock();
}

// Value used as possible argument to unique_lock's constructor.
// unique_lock objects constructed with defer_lock do not lock the mutex object automatically on construction, initializing them as not owning a lock.
// The value is a compile-time constant that carries no state, and is merely used to disambiguate between constructor signatures.
// defer_lock_t is an empty class

void deadLock1(CriticalData& a, CriticalData& b) {
    std::unique_lock<std::mutex> guard1(a.mtx, std::defer_lock); 

    std::cout << "get the first mutex" << std::endl;
    std::this_thread::sleep_for(std::chrono::microseconds(1));
    //b.mtx.lock();

    std::unique_lock<std::mutex> guard2(b.mtx, std::defer_lock);
    std::cout << "get the  second mutex" << std::endl;

    lock(guard1, guard2);
    // do something with a and b
}

// Value used as possible argument to the constructor of unique_lock or lock_guard.
// unique_lock objects constructed with adopt_lock do not lock the mutex object on construction, 
// assuming instead that it is already locked by the current thread.
// The value is a compile-time constant that carries no state, and is merely used 
// to disambiguate between constructor signatures.adopt_lock_t is an empty class

void deadLock2(CriticalData& a, CriticalData& b) {
    std::lock(a.mtx, b.mtx);

    std::lock_guard<std::mutex> guard1(a.mtx, std::adopt_lock);
    std::lock_guard<std::mutex> guard2(b.mtx, std::adopt_lock);

    std::cout << "get the first mutex" << std::endl;
    std::this_thread::sleep_for(std::chrono::microseconds(1));
    std::cout << "get the  second mutex" << std::endl;
    // do something with a and b
    
}


void deadLock3(CriticalData& a, CriticalData& b) {
    std::cout << "get the first mutex" << std::endl;
    std::this_thread::sleep_for(std::chrono::microseconds(1));
    std::cout << "get the  second mutex" << std::endl;
    // do something with a and b
    std::scoped_lock(a.mtx, b.mtx);
}

int main() {
    CriticalData c1;
    CriticalData c2;

    std::thread t1([&] { deadLock3(c1, c2); });
    std::thread  t2([&] { deadLock3(c2, c1); });

    t1.join();
    t2.join();
}
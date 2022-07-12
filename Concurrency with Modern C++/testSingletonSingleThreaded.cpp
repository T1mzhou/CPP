#include <atomic>
#include <chrono>
#include <iostream>
#include <future>
#include <mutex>

constexpr auto tenMill = 10000000;

// 0.117413->4 * tenMill
// 0.721443 // 4thread
class MySingLetion {
public:
    static MySingLetion& getInstance() {
        static MySingLetion instance;
        volatile int dummy{};
        return instance;
    }

private:
    MySingLetion() = default;
    ~MySingLetion() = default;
    MySingLetion(const  MySingLetion&) = delete;
    MySingLetion& operator=(const MySingLetion&) = delete;
};

std::mutex myMutex;

// 100.918
class MySingLetionLock {
public:
    static MySingLetionLock& getInstance() {
       std::lock_guard<std::mutex> myLock(myMutex);
       
       if (!instance) {
           instance = new MySingLetionLock();
       }

       volatile int dummy{};
       return *instance;

    }

private:
    MySingLetionLock() = default;
    ~MySingLetionLock() = default;
    MySingLetionLock(const  MySingLetionLock&) = delete;
    MySingLetionLock& operator=(const MySingLetionLock&) = delete;

    static MySingLetionLock* instance;
};

MySingLetionLock* MySingLetionLock::instance = nullptr;


// 3.45973
class MySingLetionOnceFlag {
public:
    static MySingLetionOnceFlag& getInstance() {
       std::call_once(initInstanceFlag, &MySingLetionOnceFlag::initSingleton);
       volatile int dummy{};
       return *instance;

    }

private:
    MySingLetionOnceFlag() = default;
    ~MySingLetionOnceFlag() = default;
    MySingLetionOnceFlag(const  MySingLetionOnceFlag&) = delete;
    MySingLetionOnceFlag& operator=(const MySingLetionOnceFlag&) = delete;

    static MySingLetionOnceFlag* instance;
    static std::once_flag initInstanceFlag;

    static void initSingleton() {
        instance = new MySingLetionOnceFlag;
    }
};
MySingLetionOnceFlag* MySingLetionOnceFlag::instance = nullptr;
std::once_flag MySingLetionOnceFlag::initInstanceFlag;

// 5.29612
class MySingLetionAtomic {
public:
    static MySingLetionAtomic& getInstance() {
       MySingLetionAtomic* sin = instance.load();
       if  (!sin) {
           std::lock_guard<std::mutex> myLock(myMutex);
           sin = instance.load(std::memory_order_relaxed);
           if  (!sin) {
               sin  = new MySingLetionAtomic();
               instance.store(sin);
           }
       }
       volatile int dummy{};
       return *instance;

    }

private:
    MySingLetionAtomic() = default;
    ~MySingLetionAtomic() = default;
    MySingLetionAtomic(const  MySingLetionAtomic&) = delete;
    MySingLetionAtomic& operator=(const MySingLetionAtomic&) = delete;

    static std::atomic<MySingLetionAtomic*> instance;
    static std::mutex myMutex;
};

std::atomic<MySingLetionAtomic*> MySingLetionAtomic::instance;
std::mutex MySingLetionAtomic::myMutex;


// 4.01891
class MySingLetionAcquireRelease {
public:
    static MySingLetionAcquireRelease& getInstance() {
       MySingLetionAcquireRelease* sin = instance.load(std::memory_order_acquire);
       if  (!sin) {
           std::lock_guard<std::mutex> myLock(myMutex);
           sin = instance.load(std::memory_order_release);
           if  (!sin) {
               sin  = new MySingLetionAcquireRelease();
               instance.store(sin);
           }
       }
       volatile int dummy{};
       return *instance;

    }

private:
    MySingLetionAcquireRelease() = default;
    ~MySingLetionAcquireRelease() = default;
    MySingLetionAcquireRelease(const  MySingLetionAcquireRelease&) = delete;
    MySingLetionAcquireRelease& operator=(const MySingLetionAcquireRelease&) = delete;

    static std::atomic<MySingLetionAcquireRelease*> instance;
    static std::mutex myMutex;
};

std::atomic<MySingLetionAcquireRelease*> MySingLetionAcquireRelease::instance;
std::mutex MySingLetionAcquireRelease::myMutex;


std::chrono::duration<double> getTime() {
    const auto begin = std::chrono::system_clock::now();

    for (size_t i = 0; i <= tenMill; i++) {
        MySingLetion::getInstance();
    }

    return std::chrono::system_clock::now() - begin;  
}

std::chrono::duration<double> getTimeLock() {
    const auto begin = std::chrono::system_clock::now();

    for (size_t i = 0; i <= tenMill; i++) {
        MySingLetionLock::getInstance();
    }

    return std::chrono::system_clock::now() - begin;  
}

std::chrono::duration<double> getTimeOnceFlag() {
    const auto begin = std::chrono::system_clock::now();

    for (size_t i = 0; i <= tenMill; i++) {
        MySingLetionOnceFlag::getInstance();
    }

    return std::chrono::system_clock::now() - begin;  
}


std::chrono::duration<double> getTimeAtomic() {
    const auto begin = std::chrono::system_clock::now();

    for (size_t i = 0; i <= tenMill; i++) {
        MySingLetionAtomic::getInstance();
    }

    return std::chrono::system_clock::now() - begin;  
}

std::chrono::duration<double> getTimeAc() {
    const auto begin = std::chrono::system_clock::now();

    for (size_t i = 0; i <= tenMill; i++) {
        MySingLetionAcquireRelease::getInstance();
    }

    return std::chrono::system_clock::now() - begin;  
}

int main()
{
    // auto fu1 = std::async(std::launch::async, getTime);
    // auto fu2 = std::async(std::launch::async, getTime);
    // auto fu3 = std::async(std::launch::async, getTime);
    // auto fu4 = std::async(std::launch::async, getTime);

    // auto fu1 = std::async(std::launch::async, getTimeLock);
    // auto fu2 = std::async(std::launch::async, getTimeLock);
    // auto fu3 = std::async(std::launch::async, getTimeLock);
    // auto fu4 = std::async(std::launch::async, getTimeLock);

    // auto fu1 = std::async(std::launch::async, getTimeOnceFlag);
    // auto fu2 = std::async(std::launch::async, getTimeOnceFlag);
    // auto fu3 = std::async(std::launch::async, getTimeOnceFlag);
    // auto fu4 = std::async(std::launch::async, getTimeOnceFlag);
    // auto fu1 = std::async(std::launch::async, getTimeAtomic);
    // auto fu2 = std::async(std::launch::async, getTimeAtomic);
    // auto fu3 = std::async(std::launch::async, getTimeAtomic);
    // auto fu4 = std::async(std::launch::async, getTimeAtomic);

    auto fu1 = std::async(std::launch::async, getTimeAc);
    auto fu2 = std::async(std::launch::async, getTimeAc);
    auto fu3 = std::async(std::launch::async, getTimeAc);
    auto fu4 = std::async(std::launch::async, getTimeAc);

    const auto total = fu1.get() + fu2.get() + fu3.get() + fu4.get();

    std::cout << total.count() << std::endl;
}
    
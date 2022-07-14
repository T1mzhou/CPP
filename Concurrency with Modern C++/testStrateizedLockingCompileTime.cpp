#include <iostream>
#include <mutex>
#include <shared_mutex>

template <typename LOCK>
class StrategizedLocking {
private:
    LOCK& lock;
public:
    StrategizedLocking(LOCK& l) : lock(l) {
        lock.lock();
    }

    ~StrategizedLocking() {
        lock.unlock();
    }
};

struct NullObejectMutex {
    void lock() {};
    void unlock() {};
};

class Nolock {
public:
    void lock() const {
        std::cout << "NoLock::lock: " << std::endl;
        nullObjectMutex.lock();
    }

    void unlock() const {
        std::cout << "NoLock::unlock: " << std::endl;
        nullObjectMutex.unlock();
    }

    mutable NullObejectMutex nullObjectMutex;
};

class ExclusiveLock {
public:
    void lock() const {
        std::cout << "ExclusiveLock::lock: " << std::endl;
        m_mutex.lock();
    }

    void unlock() const {
        std::cout << "ExclusiveLock::unlock: " << std::endl;
        m_mutex.unlock();
    }

    mutable std::mutex m_mutex;
};

class SharedLock  {
public:
    void lock()  const {
        std::cout << "SharedLock::lock: " << std::endl;
        sharedMutex.lock();
    }

    void unlock() const  {
        std::cout << "SharedLock::unlock: " << std::endl;
        sharedMutex.unlock();
    }

    mutable std::shared_mutex sharedMutex;
};


int main() {
    std::cout << std::endl;

    Nolock nolock;
    StrategizedLocking Strategy1{ nolock };

    {
        ExclusiveLock exLock;
        StrategizedLocking Strategy2{ exLock };
        {
            SharedLock sharLock;
            StrategizedLocking Strategy3{ sharLock };
        }
    }

    std::cout << std::endl;
}
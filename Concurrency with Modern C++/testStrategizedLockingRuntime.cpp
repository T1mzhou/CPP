#include <iostream>
#include <mutex>
#include <shared_mutex>

class Lock {
public:
    virtual void lock() const = 0;
    virtual void unlock() const = 0;
};

class StrategizedLocking {
private:
    Lock& lock;
public:
    StrategizedLocking(Lock& l) : lock(l) {
        lock.lock();
    }
    ~StrategizedLocking() {
        lock.unlock();
    }
};

struct NullObjectMutex {
    void lock() { };
    void unlock() { };
};

class Nolock : public Lock {
    void lock() const override {
        std::cout << "Nolock::lock: " << std::endl;
        nullObjectMutex.lock();
    }

    void unlock() const override {
        std::cout << "Nolock::unlock: " << std::endl;
        nullObjectMutex.unlock();
    }
private:
    mutable NullObjectMutex nullObjectMutex;
};

class ExclusiveLock : public Lock {
    void lock() const override {
        std::cout << "ExclusiveLock::lock: " << std::endl;
        mutex.lock();
    }

    void unlock() const override {
        std::cout << "ExclusiveLock::unlock: " << std::endl;
        mutex.unlock();
    }
private:
    mutable std::mutex mutex;
};

class SharedLock : public Lock {
    void lock() const override {
        std::cout << "SharedLock::lock: " << std::endl;
        sharedMutex.lock();
    }

    void unlock() const override {
        std::cout << "SharedLock::unlock: " << std::endl;
        sharedMutex.unlock();
    }
private:
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
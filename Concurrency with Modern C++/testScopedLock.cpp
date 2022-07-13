#include <iostream>
#include <mutex>
#include <new>
#include <string>
#include  <utility>

class ScopedLock {
public:
    explicit ScopedLock(std::mutex& m) : m_mtx(m) {
        m_mtx.lock();
        std::cout << "Lock the mutex: " << &m_mtx << std::endl;
    }

    ~ScopedLock() {
        std::cout << "Release the mutex: " << &m_mtx  << std::endl;
        m_mtx.unlock();
    }
private:
    std::mutex& m_mtx;
};

int main()
{
    std::cout << std::endl;

    std::mutex mtx1;
    ScopedLock splk{mtx1};

    std::cout << "\nBefore local scope" << std::endl;
    {
        std::mutex mtx2;
        ScopedLock splk{mtx2};
    }

    std::cout << "After local scope" << std::endl;

    std::cout << "\nBefore try-catch block" << std::endl;

    try {
        std::mutex mtx3;
        ScopedLock splk{mtx3};
        throw std::bad_alloc();
    }
    catch (std::bad_alloc& e) {
        std::cout << e.what();
    }

    std::cout << "\nAfter try-catch block" << std::endl;

    std::cout << std::endl;
}
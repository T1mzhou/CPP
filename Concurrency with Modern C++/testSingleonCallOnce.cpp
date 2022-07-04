#include <iostream>
#include <mutex>
#include <thread>

using namespace std;

class MySingleton {
public:
    MySingleton(const MySingleton&) = delete;
    MySingleton& operator=(const MySingleton&) = delete;

    static MySingleton* getInstance() {
        call_once(initInstanceFlag, MySingleton::initSingleton);
        return instance;
    }

    static void initSingleton() {
        instance = new MySingleton();
    }
private:
    static once_flag initInstanceFlag;
    static MySingleton*instance;
    MySingleton() = default;
    ~MySingleton() = default;
};

MySingleton* MySingleton::instance = nullptr;
once_flag MySingleton::initInstanceFlag;

int main() {
    cout << endl;
    cout << "MySingleton::getInstance(): " << MySingleton::getInstance() << endl;
    cout << "MySingleton::getInstance(): " << MySingleton::getInstance() << endl;

    std::thread t1([]{ cout << "t1 MySingleton::getInstance(): " << MySingleton::getInstance() << endl;});
    std::thread t2([]{ cout << "t2 MySingleton::getInstance(): " << MySingleton::getInstance() << endl;});

    t1.join();
    t2.join();
    cout << endl;
}
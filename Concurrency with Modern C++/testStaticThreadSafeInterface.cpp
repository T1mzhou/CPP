#include <iostream>
#include <mutex>
#include <shared_mutex>
#include <thread>

class Critical {
public:
    void interface1() const {
        std::lock_guard<std::mutex>  lock_guard(mut);
        implementtation1();
    }

    void interface2() {
        std::lock_guard<std::mutex> lock_guard(mut);
        implementtation2();
        implementtation3();
        implementtation1();
    }

private:
    void implementtation1() const {
        std::cout <<  " implementation1: " <<
            std::this_thread::get_id() << std::endl;
    }

    void implementtation2() const {
        std::cout <<  " implementation2: " <<
            std::this_thread::get_id() << std::endl;
    }

    void implementtation3() const {
        std::cout <<  " implementation3: " <<
            std::this_thread::get_id() << std::endl;
    }

    inline static int  called{ 0 };
    inline static std::mutex mut;
};

int main()
{
    std::cout << std::endl;

    std::thread t1([] {
        const  Critical crit;
        crit.interface1();
    });

    std::thread t2([] {
        Critical crit;
        crit.interface2();
        crit.interface1();
    });

    Critical crit;
    crit.interface1();
    crit.interface2();

    t1.join();
    t2.join();

    std::cout << std::endl;
}
#include <stdexcept>
#include <thread>
#include <utility>
#include <iostream>

class scoped_thread {
std::thread t;
public:
    explicit scoped_thread(std::thread t_) : t(std::move(t_)) {
        if (!t.joinable()) throw std::logic_error("No thread");
    }

    ~scoped_thread() {
        t.join();
    }

    scoped_thread(scoped_thread&) = delete;
    scoped_thread& operator=(scoped_thread const &) = delete;
};

int main() {
    std::thread t4([] {std::cout << std::this_thread::get_id() << std::endl;}); // 生命周期问题,没有join火和etach导致。
    scoped_thread(std::move(t4)); // 使用scpred_thread解决
}
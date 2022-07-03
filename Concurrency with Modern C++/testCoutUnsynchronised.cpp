#include <chrono>
#include <iostream>
#include <thread>
#include <mutex>

std::mutex countMtx;

// C++11 cout是线程安全的，输出的问题是有因为写入是一个种竞态的条件，完全取决于交错运行的线程

class Worker {
public:
    Worker(std::string n) : name(n) {}
    void operator() () {
        for (int i = 0; i <= 3; i++) {
            // begin work
            std::this_thread::sleep_for(std::chrono::microseconds(200));
            // end work
            countMtx.lock();
            std::cout << name << ": " << "Work " << i << " done !!!" << std::endl;
            countMtx.unlock();
        }
    }
private:
    std::string name;
};

int main() {
    std::cout << std::endl;

    std::cout << "Bos: Let's start working.\n\n";

    std::thread herb = std::thread(Worker("Herb"));
    std::thread andrei = std::thread(Worker(" Andrei"));
    std::thread scott = std::thread(Worker("  Scott"));
    std::thread njarne = std::thread(Worker("   Bjarne"));
    std::thread nart = std::thread(Worker("    Bart"));
    std::thread jenne = std::thread(Worker("     Jenne"));

    herb.join();
    andrei.join();
    scott.join();
    njarne.join();
    nart.join();
    jenne.join();

    std::cout << "\n" << "Boss: Let's go home." << std::endl;

    std::cout << std::endl;

}
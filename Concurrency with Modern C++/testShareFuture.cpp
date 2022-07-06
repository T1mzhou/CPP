#include <future>
#include <iostream>
#include <mutex>
#include <utility>
#include <thread>

std::mutex mtx;

struct Div {
    void operator() (std::promise<int>&& intPromise, int a, int b) const {
        intPromise.set_value(a / b);
    }
};

struct Requestor {
    void operator()(std::shared_future<int> shaFut) {
        // lock std::cout
        std::lock_guard<std::mutex> guard(mtx);
        
        // get threaed id
        std::cout << "ThreadId(" << std::this_thread::get_id() << "):";

        std::cout << "20/10= " << shaFut.get() << std::endl;
    }
};

int main() {
    std::cout << std::endl;

    // define the promises
    std::promise<int> divPromise;

    // get the futures
    std::shared_future<int> divRes = divPromise.get_future();

    // calcaute the res int a separete thread
    Div div;
    std::thread divThread(div, std::move(divPromise), 20, 10);

    Requestor req;
    std::thread shareThread1(req, divRes);
    std::thread shareThread2(req, divRes);
    std::thread shareThread3(req, divRes);
    std::thread shareThread4(req, divRes);
    std::thread shareThread5(req, divRes);

    divThread.join();

    shareThread1.join();
    shareThread2.join();
    shareThread3.join();
    shareThread4.join();
    shareThread5.join();

    std::cout << std::endl;
    
}
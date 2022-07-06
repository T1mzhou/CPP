#include <future>
#include <ios>
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
    std::cout << std::boolalpha << std::endl;

    // define the promises
    std::promise<int> divPromise;

    // get the futures
    std::future<int> divRes = divPromise.get_future();

    std::cout << "divResult.valid(): " << divRes.valid() << std::endl;

    // calcaute the res int a separete thread
    Div div;
    std::thread divThread(div, std::move(divPromise), 20, 10);

    std::cout << "divResult.valid(): " << divRes.valid() << std::endl;

    std::shared_future<int> sharedRes = divRes.share();

    std::cout << "divResult.valid(): " << divRes.valid() << "\n\n";

    Requestor req;
    std::thread shareThread1(req, sharedRes);
    std::thread shareThread2(req, sharedRes);
    std::thread shareThread3(req, sharedRes);
    std::thread shareThread4(req, sharedRes);
    std::thread shareThread5(req, sharedRes);

    divThread.join();

    shareThread1.join();
    shareThread2.join();
    shareThread3.join();
    shareThread4.join();
    shareThread5.join();

    std::cout << std::endl;
    
}
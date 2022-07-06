#include <future>
#include <iostream>
#include <utility>
#include <thread>

void product(std::promise<int>&& intPromise, int a, int b) {
    intPromise.set_value(a *b);
}

struct Div {
    void operator() (std::promise<int>&& intPromise, int a, int b) const {
        intPromise.set_value(a / b);
    }
};


int main() {
    int a = 20;
    int b = 10;

    std::cout << std::endl;

    // define the promises
    std::promise<int> prodPromise;;
    std::promise<int> divPromise;

    // get the futures
    std::future<int> prodRes = prodPromise.get_future();
    std::future<int> divRes = divPromise.get_future();

    // calculate the res in a separeate thread
    std::thread prodThread(product, std::move(prodPromise), a, b);

    Div div;
    std::thread divThread(div, std::move(divPromise), a, b);

    // get the result
    std::cout << "20 * 10 = " << prodRes.get() << std::endl;
    std::cout << "20 / 10 = " << divRes.get() << std::endl;

    prodThread.join();
    divThread.join();

    std::cout << std::endl;
}
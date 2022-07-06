#include <future>
#include <exception>
#include <iostream>
#include <mutex>
#include <stdexcept>
#include <string>
#include <utility>
#include <thread>

struct Div {
    void operator() (std::promise<int>&& intPromise, int a, int b) const {

        try {
            if ( b == 0 ) {
                std::string errMess = std::string("Illegal division by zero: ") + std::to_string(a) + "/" +\
                                    std::to_string(b);
                throw std::runtime_error(errMess);
            }

            intPromise.set_value(a / b);
        
        } catch (...) {
            intPromise.set_exception(std::current_exception());
        }
        
    }
};

void executeDivision(int nom, int denom) {
    std::promise<int> divPromise;
    std::future<int> divRes = divPromise.get_future();

    Div div;

    std::thread divThread(div , std::move(divPromise), nom, denom);

    // get the result or the exception
    try {
        std::cout << nom << "/" << denom << " = " << divRes.get() << std::endl;
    } catch (std::runtime_error& e) {
        std::cout << e.what() << std::endl;
    }

    divThread.join();
}

int main() {
    std::cout << std::endl;

    executeDivision(20, 0);
    executeDivision(20, 10);

    std::cout << std::endl;
}
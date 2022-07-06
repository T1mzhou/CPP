#include <future>
#include <iostream>
#include <thread>
#include <chrono>

using namespace std::literals::chrono_literals;

void getAnswer(std::promise<int> intPromise) {
    std::this_thread::sleep_for(3s);
    intPromise.set_value(42);
}

int main() {
    std::cout << std::endl;

    std::promise<int> anserPromise;
    auto fut = anserPromise.get_future();

    std::thread prodThread(getAnswer, std::move(anserPromise));

    std::future_status status{};
    do {
        status = fut.wait_for(0.2s);
        std::cout << "... doing something else" << std::endl;
    } while (status != std::future_status::ready);

    std::cout << std::endl;

    std::cout << "The Answer: " << fut.get() << '\n';

    prodThread.join();

    std::cout << std::endl;
}
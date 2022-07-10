#include <algorithm>
#include <execution>
#include <pstl/glue_execution_defs.h>
#include <vector>
#include <mutex>
#include <iostream>


std::mutex m;

int main() {
    std::vector<int> v = { 1, 2, 3};

    std::atomic<int> sum = 0; // 防止lamda表达式连续两次调用m.lock;

    std::for_each(std::execution::par_unseq, v.begin(), v.end(),
        [&sum](int i) {
            std::lock_guard<std::mutex> lock(m);
            sum += i + i;
        }
    );

}
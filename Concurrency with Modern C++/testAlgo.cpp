#include <execution>
#include <vector>
#include <algorithm>
#include <iostream>

// note C++ 17 标准编译器可以

int main() {
    std::vector<int>  t = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    // standard sequemtial sort
    std::sort(t.begin(), t.end());

    for (auto i : t) {
        std::cout << i << std::endl;
    }

    // sequential execution 串行
    std::sort(std::execution::seq, t.begin(), t.end());

    // permitting parallel execution 冰箱
    std::sort(std::execution::par, t.begin(), t.end());

    // permitting parallel and vectorized execution 多个线程上并行，可以循环交叉
    std::sort(std::execution::par_unseq, t.begin(), t.end());

}
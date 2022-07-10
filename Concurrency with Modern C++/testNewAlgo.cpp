#include <algorithm>
#include <execution>
#include <numeric>
#include <iostream>
#include <string>
#include <vector>
#include <vector>

int main() {
    std::cout << std::endl;

    // for_each_n

    std::vector<int> intVec{ 1 , 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    std::for_each_n(std::execution::par,
        intVec.begin(), 5, [](int& arg) { arg *= arg; }
    );

    std::cout << "for_each_n: ";
    for (auto v : intVec) {
        std::cout << v << " ";
    }

    std::cout << "\n\n";
}
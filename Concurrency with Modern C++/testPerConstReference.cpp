#include <thread>

class NonCopyableClass {
public:
    NonCopyableClass() = default;

    NonCopyableClass& operator=(const NonCopyableClass&) = delete;
    NonCopyableClass(const NonCopyableClass&) = delete;
};

void perConstReference(const NonCopyableClass& nonCopy) {}

int main() {
    NonCopyableClass nonCopy;

    perConstReference(nonCopy); //不可以复制

    std::thread t(perConstReference, nonCopy);

    t.join();
}
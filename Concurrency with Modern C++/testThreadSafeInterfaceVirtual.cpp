#include <iostream>
#include <mutex>
#include <thread>

class Base {
public:
    virtual void interface() {
        std::lock_guard<std::mutex> lock_guard(mut);
        std::cout << "Base with lock" << std::endl;
    }
private:
    std::mutex mut;
};

class Derived : public Base {
    void interface() override {
        std::cout << "Derived without lock" << std::endl;
    };
};

int main()
{
    std::cout << std::endl;

    Base* base1 = new Derived;
    base1->interface();

    Derived der;
    Base& base2 = der;
    base2.interface();

    std::cout << std::endl;
}
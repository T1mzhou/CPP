#include <iostream>
#include <memory>

class Strategy {
public:
    virtual void operator() () = 0;
    virtual ~Strategy() = default;
};

class Context {
private:
    std::shared_ptr<Strategy> _start;
public:
    explicit Context() : _start(nullptr) {}
    void setStrategy(std::shared_ptr<Strategy> start) {
        _start = start;
    }
    void Strategy() {
        if ( _start ) {
            (*_start)();
        }
    }
};

class Strategy1 : public Strategy {
    void operator() () override {
        std::cout << "Foo" << std::endl;
     }
};

class Strategy2 : public Strategy {
    void operator() () override {
        std::cout << "Bar" << std::endl;
     }
};


class Strategy3 : public Strategy {
    void operator() () override {
        std::cout << "FooBar" << std::endl;
     }
};

int main()
{
    std::cout << std::endl;

    Context con;

    con.setStrategy(std::shared_ptr<Strategy>(new Strategy1));
    con.Strategy();

    con.setStrategy(std::shared_ptr<Strategy>(new Strategy2));
    con.Strategy();

    con.setStrategy(std::shared_ptr<Strategy>(new Strategy3));
    con.Strategy();

    std::cout << std::endl;
}
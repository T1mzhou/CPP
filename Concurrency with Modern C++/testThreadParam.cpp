#include <iostream>
#include <thread>
#include <string>
#include <functional>

void test(const std::string& a)
{
    std::cout << "test = " << a << std::endl;
}

void testCopyOrRef() {
    std::string s{"C++11"};

    std::thread t1([=] {std::cout << s << std::endl; });
    t1.join();

    std::thread t2([&]{ std::cout << s << std::endl; }); // t2并通过引用来获取参数,而是lambda表达式通过引用来捕获参数
    t2.detach();                                         // 未定义问题：全局对象std::cout与主线程的生存周期绑定，可能生命周期比线程t2短;

    //std::thread t3(test, std::ref(s));
    //t3.join();
}

int main() {
    testCopyOrRef();
    
    return 0;
}
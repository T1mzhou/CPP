#include <iostream>
#include <type_traits>

void decltypeDemo()
{
    int x1 = 0;
    decltype(x1) x2 = 0;
    std::cout << typeid(x2).name() << std::endl; // x2 is int 

    double x3 = 0;
    decltype(x1 + x3) x4 = x1 + x3;
    std::cout << typeid(x4).name() << std::endl; // x1 + x3的类型为double

   // decltype({1, 2}) x5; // err不是表达式

}

// 在非静态成员变量中使用
struct S1 {
    int x1;
    decltype(x1) x2;
    double x3;
    decltype(x2 + x3) x4;
};

// 在函数形参中使用
int x1 = 0;
decltype(x1) sum(decltype(x1) a1, decltype(a1) a2) {
    return a1 + a2;
}

void decltypeDemo1()
{
    auto x2 = sum(5 , 10);
    std::cout << x2 << std::endl;
}

// decltype解决泛型函数模板需要指定返回值类型的问题
// 仅建议在C++11中使用,C++14已经支持auto返回类型推导
template <class T1, class T2>
auto sum(T1 a1, T2 a2)->decltype(a1 + a2)
{
    return a1 + a2;
}

void decltypeDemo2()
{
    auto x4 = sum(5, 10.5);
    std::cout << x4 << std::endl;
}

// 如果想正确返回引用类型，需要使用导decltype,auto会被推导为值类型
template <class T>
auto return_ref(T& t)->decltype(t)
{
    return t;
}

void decltypeDemo3()
{
    int x1 = 0;
    static_assert(
        std::is_reference_v<decltype(return_ref(x1))>
    );
}


int main() {
    decltypeDemo();
    decltypeDemo1();
    decltypeDemo2();
    decltypeDemo3();
    
    return 0;
}
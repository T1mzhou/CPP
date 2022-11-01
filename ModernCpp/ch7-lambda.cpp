#include <iostream>
#include <vector>
#include <algorithm>
#include <future>

// 定义
// [captures](params) specifiers exception -> ret { body }
// params 参数可选
// ret exception 可选
// 所以最简单的lambda为[]{}
void lambdaDemo()
{
    int x = 5;
    auto foo = [x](int y)->int { return x * y; };
    std::cout << foo(8) << std::endl;
}

// 捕获的变量必须是自动存储的数据类型
// 自动生存期（automatic storage duration）在函数定义（特殊的代码块，包括函数参数）或者代码块中声明的变量，
// 又称为自动变量（automatic variable）。程序执行进入代码块时分配内存（内存区栈stack）创建变量，离开（执行完代码块内代码）时，回收（释放）内存
// 实际测试堆上的变量也可以

int x = 0;

void lamdaDemo1()
{
    int y = 0;
    static int z = 0;
    int * p = new int(1);
   // auto foo = [x, y, z, p] { std::cout << "x = " << x << "y = " << y << "z = " << z << "*p = " << *p << std::endl; };
   // error
   // error: 'x' cannot be captured because it does not have automatic storage duration
   // 'z' cannot be captured because it does not have automatic storage duration

   auto foo = [y, p] { std::cout << "y = " << y << " z = " << *p << std::endl; };

   delete p;

    foo();
}

void lambdaDemo2()
{
    int y = 2;
    static int z = 3;
    auto foo = [y] { return x + y + z; };
    std::cout << foo() << std::endl;
}


auto foo =  [] { return x; };

void lambdaDemo3()
{
    int x = 5, y = 8;
    auto foo = [&x, &y] { 
        x += 1;
        y += 2;
        return x * y;
    };

    std::cout << foo() << std::endl;
}

// 使用mutable移除lambda表达式的常量属性
// 但是和引用不一样,引用会改变引用变量的值，而mutable智能改动内部捕获变量的值
void lambdaDemo4()
{
    int x = 5, y = 8;
    auto foo = [x, y]() mutable {
        x += 1;
        y += 2;
        return x * y;
    };   

    std::cout << foo() << std::endl;
    std::cout << "x = " << x << " y = " << y << std::endl;
}

// [this] 捕获this指针
// [=] 捕获lambda表达式定义作用域的全部变量的值，包括this
// [&] 捕获lambda表达式定义作用域的全部变量的引用，包括this

class A {
public:
    void print() {
        std::cout << "Class A " << x << std::endl;
    }

    void test() {
        auto foo = [this] {
            x = 5;
            print();
        };
        foo();
    }

private:
    int x;
};

void lambdaDemo5()
{
    A a;
    a.test();
}

void lambdaDemo6()
{
    int x = 5, y = 8;
    auto foo = [=] { return x * y; };
    std::cout << foo() << std::endl;
}

// 无状态lambda表达式可以隐式转换为函数指针

void f(void(*)()) {}
void f1(void(&)()) {}

void lambdaDemo7()
{
    f([]{}); // 编译欧克
    f(*[] {});
}

// lambda in STL
void lambdaDemo8()
{
    std::vector<int> x = {1, 2, 3, 4,  5};
    std::cout << *std::find_if(x.cbegin(),
                            x.cend(),
                            [](int i) { return (i % 3) == 0;}) << std::endl;

}

// 广义捕获
// 1.简单不会，前面的都是
// 2.初始化捕获，解决了简单捕获的一个重要问题，既只能捕获lambda表达式上下文的变量
// 而无法捕获表达式解决过以及自定义捕获变量名

// 未定义 
// class Work {
// private:
//     int value;

// public:
//     Work() : value(42) {}
//     std::future<int> spawn() {
//         return std::async([=]()-> int { return value; });
//     }
// };

// 解决方案
class Work {
private:
    int value;

public:
    Work() : value(42) {}
    std::future<int> spawn() {
        return std::async([=, tmp = *this]()-> int { return tmp.value; });
    }
};

std::future<int> foo1()
{
    Work tmp;
    return tmp.spawn();
}

void lambdaDemo9()
{
    int x = 5;
    auto foo = [x = x + 1] {return x; }; //C++11 不行

    std::cout << foo() << std::endl;

    // 场景1
    std::string x1 = "Hello C++";
    auto foo1 = [x1 = std::move(x1)] { return x1 + "world"; };
    // 使用std::move对捕获列表变量x进行初始化,避免了值拷贝，直接复制对象提高了效率

    // 场景2
    // 异步调用时复制this对象,防止lambda表达式被调用时因玉环市this对象被析构而造成未定义的行为

    // std::future<int> f1 = foo1();
    // f1.wait();
    // std::cout << "f.get() = " << f1.get() << std::endl;


}

int main() {
    lambdaDemo();
    lamdaDemo1();
    lambdaDemo2();
    std::cout << foo() << std::endl;
    lambdaDemo3();
    lambdaDemo4();
    lambdaDemo5();
    lambdaDemo6();
    lambdaDemo7();
    lambdaDemo8();

    return 0;
}

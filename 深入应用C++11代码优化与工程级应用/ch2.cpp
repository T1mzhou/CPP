#include <iostream>

using namespace std;

// 1.右值引用(T&&)
// 概念:分为将亡值和纯右值
// 纯右值:非引用返回的临时变量,运算符表达式产生的临时变量,原始字面量,和lambda表达式等
// 将亡值:将要被移动的对象,T&&函数返回值,std::move返回值和转换为T&&d的类型的转换函数的返回值
// C++中的值必然是:左值，将亡值,纯右值。区分右值和左值是否可以取地址&;
// 右值引用就是对一个右值进行引用的类型
// 注意：声明左值还是右值引用都必须立即进行初始化,因为引用类型本身并不拥有所绑定对象的内存

int g_constructCount = 0;
int g_copyConstructCount = 0;
int g_destructCount = 0;

struct A
{
    A() {
        cout << "CONSTRUCT: " << ++g_constructCount << endl;
    }

    A(const A& a)
    {
        cout << "COPY construct: " << ++g_copyConstructCount << endl;
    }

    ~A()
    {
        cout << "destruct: " << ++g_destructCount << endl;
    }
};

A GetA()
{
    return A(); //构造临时对象返回调用拷贝构造函数
}

void testRightRef()
{
    //A a = GetA(); // 构造a对象产生
    A&& a = GetA();
}

// 第二次的dectruct是因为临时对象在构造a对象后就销毁了

int main()
{
    testRightRef();
    return 0;
}

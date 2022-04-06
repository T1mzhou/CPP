#include <iostream>
#include <map>

using namespace std;

// auto占位符,使用其声明的变量必须马上初始化,编译器才会知道其实际类型
// 结论：1.当不声明为指针或引用时,auto的推导结果和初始化表达式抛弃引用和CV限定符后类型一致
//      2.当声明为指针或者引用时,auto的推导结果讲保持初始化表达式的CV属性
// 限制：1.auto 不能用于函数参数
//      2.auto 不能用于非静态成员变量(仅能用于推导static和枚举成员，因为其他静态类型在C++中不能就地初始化)
//      3.auto 无法定义数组
//      4.auto 无法推导除模板参数
// 什么时候用:
//      1.stl容器遍历
//      2.简化函数定义
// void func(auto a = 1) { }       // error:auto不能用于函数参数

struct Foo
{
    //auto var1_ = 0;                // error：auto不能用于非静态成员函数
    static const auto var2_ = 0;
};

template < typename T >
struct Bar {};


class Test
{
public:
    static int get(void)
    {
        return 0;
    }
};

class Bar1
{
public:
    static const char* get(void)
    {
        return "0";
    }
};

template < class A >
void func(void)
{
    auto val = A::get(); // 定义一个泛型的变量
    // ....
}

void testAuto()
{
    auto x = 5;                 // x is int, 5 is const int, const被丢弃了
    auto pi = new auto(1);      // pi is int*
    const auto *v = &x, u = 6;  // v is const int* u is const int
    static auto y = 0.0;        // y is double
   // auto int r;               // error:auto不再表示存储类型指示符
   // auto s;                   // error:auto无法推导出s的类型

   // auto与CV限定符结合使用
    int a = 5;

    auto *b = &a;               // b -> int*, auto -> int
    auto c = &a;                // c -> int *, auto -> int *
    auto & d = a;               // d -> int&, auto -> int

    const auto e = a;           // e -> const int, auto ->int
    auto f = e;                 // f -> int, auto -> int //error 会去掉const

    const auto& g = a;          // g -> const int&, auto -> int //
    auto& h = g;                // h -> const int&, auto -> const int // 当auto和引用/指针结合时,auto推到会保留const属性

    // auto限制
    int arr[10] = { 0 };
    auto aa = arr;              // ok aa->int*
   // auto rr[10] = arr;        // error: auto 无法定义数组

    Bar<int> bar;
   // Bar<auto> bb = bar;         // error：auto无法推导除模板参数

   // 什么时候用auto
   // before
    std::map<double, double> resultMap;

    std::map<double, double>::iterator it = resultMap.begin();

    for (; it != resultMap.end(); ++it)
    {
        // do something
    }

    // after
    for (auto it = resultMap.begin(); it != resultMap.end(); ++it)
    {
        // do something;
    }

    // 简化函数定义
    func<Test>();
    func<Bar1>();

}

int main()
{
    testAuto();

    return 0;
}

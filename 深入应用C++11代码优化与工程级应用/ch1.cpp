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

// decltype
// 推导规则:
//        1.exp是标识符,类访问表达式,decltype(exp)和exp的类型一致
//        2.exp是函数调用,decltype(exp)和返回值的类型一致
//        3.其他情况,若exp是一个左值,则decltype(exp)是exp类型的左值引用，否则和exp类型一致
// 应用：
//       1.泛型编程
//       2.返回类型后置语法
class Foo2
{
 public:
    static const int Number = 0;
    int x;
};


int& func_int_r(void); // 左值
int&& func_int_rr(void); //x值，xvalue
int func_int(void);      //纯右值

const int& func_cint_r(void); // 左值
const int&& func_cint_rr(void); // x值
const int func_cint(void); // 纯右值
const Foo2 func_cfoo(void); // 纯右值

struct Foo3{
    int x;
};

template <class ContainterT>
class Foo4
{
    decltype (ContainterT().begin()) it_; // 没有类型推导,需要去特化const类型
public:
    void func(ContainterT& container)
    {
        it_ = container.begin();
    }
};

template <typename T, typename U>
auto add(T t, U u) -> decltype (t + u)
{
    return t + u;
}

void testDecltype()
{
    int x = 0;
    decltype(x) y = 1;          // y -> int
    decltype(x + y) z = 0;      // z -> int

    const int& i = x;
    decltype(i) j = y;          // i -> const int&

    const decltype(z) * p = &z; // p ->const int*
    decltype(z) * pi = &z;      // pi -> int*
    decltype(pi) * pp = &pi;    // pp -> int**

    // 标识符表达式和类访问表达式
    int n = 0;
    volatile const int & x1 = n;

    decltype (n) a = n;   // int
    decltype (x1) b = n;  // volatile const int &

    decltype (Foo2::Number) c = 0; // const int

    Foo2 foo;
    decltype (foo.x) d = 0; // d ->int

    // 函数调用
    decltype (func_int_r()) a1 = x;   // a1 -> int &
    decltype (func_int_rr()) b1 = 0;  // b1 -> int&&
    decltype (func_int()) c1 = 0;     // c1 -> int
    decltype (func_cint_r()) a2 = x;  // a2 -> const int&
    decltype (func_cint_rr()) b2 = 0; // b2 -> const int&&
    decltype (func_cint()) c2 = 0;    // c2 -> const int //errror 应该返回int，因为函数返回的int是纯右值,对于纯右值而言,只有类类型才可以携带CV限定符。

    decltype(func_cfoo()) ff = Foo2(); // ff -> const Foo

    // 带扩号的表达式和加法运算表达式
    const Foo3 foo1 = Foo3();

    decltype (foo1.x) a3 = 0;     // a -> int
    decltype ((foo1.x)) b3 = a3;  // b ->? const int& foo.x是一个左值,可以知道括号表达式也是一个左值,所以是一个左值引用，并且foo1是const类型，所以是为const int&

    int n1 = 0, m = 0;
    decltype(n1 + m) c3 = 0;     // c -> int // 返回右值
    decltype(n1 += m) d3 = c3;    // c -> int& // 返回左值, 按规则3为int &

}

// 模板别名

using func_t = void (*)(int, int);
using map_int_t = std::map<std::string, int>;
using uint_t = unsigned int;

// 列表初始化
//  好处: 统一的初始化类型

struct A
{
    int x;
    int y;
} a = { 1, 2};

class Foo5
{
public:
    Foo5(int) {}

private:
    Foo5(const Foo5&);
};

struct Foo6
{
    Foo6(int, double) {}
};

Foo6 func()
{
    return {123, 321.0}; // 用于函数返回值
}



void testInitList()
{
    int i_arr[3] = { 1, 2, 3};
    long l_arr[] = { 1, 3, 2, 4};

    Foo5 a1(123);
    //Foo5 a2 = 123; // error：私有
    Foo5 a3 = { 123 };
    Foo5 a4{ 123 };

    Foo5 a5 = { 3 };
    Foo5 a6{ 3 };

    int* arr = new int[3] { 1, 2, 3};

}

int main()
{
    //testAuto();
    testDecltype();

    return 0;
}

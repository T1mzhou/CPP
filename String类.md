# String类实现

## String.h

```cpp
#ifndef __MY_STRING_H__
#define __MY_STRING_H__

#include <cstring>
#include <iostream>

class String
{
public:
    String(const char *cstr = 0);
    String(const String &str);
    String &operator=(const String &str);
    char *get_c_str() const { return m_data; }

    ~String();

private:
    char *m_data;
};

inline String::String(const char *cstr)
{
    if (cstr)
    {
        m_data = new char[strlen(cstr) + 1];
        strcpy(m_data, cstr);
    }
    else
    {
        m_data = new char[1];
        *m_data = '\0';
    }
    std::cout << "构造" << std::endl;
}

inline String::~String()
{
    delete[] m_data;
    std::cout << "析构" << std::endl;
}

inline String::String(const String &str)
{
    m_data = new char[strlen(str.m_data) + 1];
    strcpy(m_data, str.m_data);
    std::cout << "拷贝构造" << std::endl;
}

inline String &String::operator=(const String &str)
{
    if (this == &str)
    {
        return *this;
    }

    delete[] m_data;
    m_data = new char[strlen(str.m_data) + 1];
    strcpy(m_data, str.m_data);

    std::cout << "赋值构造" << std::endl;

    // return *this返回的是当前对象的克隆或者本身（若返回类型为A， 则是克隆， 若返回类型为A&， 则是本身 ）。
    // return this返回当前对象的地址（指向当前对象的指针）,
    return *this;
}

std::ostream &
operator<<(std::ostream &os, const String &str)
{
    os << str.get_c_str();
    return os;
}
#endif // __MY_STRING_H__
```

## my_string_test.cpp

```cpp
#include "my_string.h"
#include <iostream>

using namespace std;

int main()
{
    String s1("hello");
    String s2("world");

    String s3(s2);
    cout << s3 << endl;

    s3 = s1;
    cout << s3 << endl;
    cout << s2 << endl;
    cout << s1 << endl;
}
```


# complex类实现

## comlex.h

```cpp
#ifndef __COMPLEX_H__
#define __COMPLEX_H__

#include <cmath>

class complex;
complex &
__doapl(complex *ths, const complex &r);
complex &
__doami(complex *ths, const complex &r);
complex &
__doaml(complex *ths, const complex &r);

class complex
{
public:
    complex(double r = 0, double i = 0) : re(r), im(i) {}
    complex &operator+=(const complex &);
    complex &operator-=(const complex &);
    complex &operator*=(const complex &);
    complex &operator/=(const complex &);
    double real() const { return re; }
    double imag() const { return im; }

private:
    double re, im;

    friend complex &__doapl(complex *, const complex &);
    friend complex &__doami(complex *, const complex &);
    friend complex &__doaml(complex *, const complex &);
};

inline complex &
__doapl(complex *ths, const complex &r)
{
    ths->re += r.re;
    ths->im += r.im;
    return *ths;
}

inline complex &
__doami(complex *ths, const complex &r)
{
    ths->re -= r.re;
    ths->im -= r.im;
    return *ths;
}

inline complex &
__doaml(complex *ths, const complex &r)
{
    double f = ths->re * r.re - ths->im * r.im;
    ths->im = ths->re * r.im + ths->im * r.re;
    ths->re = f;
    return *ths;
}

inline complex &
complex::operator+=(const complex &r)
{
    return __doapl(this, r);
}

inline complex &
complex::operator-=(const complex &r)
{
    return __doami(this, r);
}

inline complex &
complex::operator*=(const complex &r)
{
    return __doaml(this, r);
}

inline double
real(const complex &r)
{
    return r.real();
}

inline double
imag(const complex &i)
{
    return i.imag();
}

inline complex
operator+(const complex &left, const complex &right)
{
    return complex(real(left) + real(right), imag(left) + imag(right));
}

inline complex
operator+(const complex &left, double right)
{
    return complex(real(left) + right, imag(left));
}

inline complex
operator+(double left, const complex &right)
{
    return complex(left + real(right), imag(right));
}

inline complex
operator-(const complex &left, const complex &right)
{
    return complex(real(left) - real(right), imag(left) - imag(right));
}

inline complex
operator-(const complex &left, double right)
{
    return complex(real(left) - right, imag(left));
}

inline complex
operator-(double left, const complex &right)
{
    return complex(left - real(right), imag(right));
}

inline complex
operator*(const complex &left, const complex &right)
{
    return complex(real(left) * real(right) - imag(left) * imag(right),
                   real(left) * imag(right) + imag(left) * real(right));
}

inline complex
operator*(const complex &left, double right)
{
    return complex(real(left) * right, imag(left) * right);
}

inline complex
operator*(double left, const complex &right)
{
    return complex(left * real(right), left * imag(right));
}

inline complex
operator/(const complex &left, double y)
{
    return complex(real(left) / y, imag(left) / y);
}

inline complex
operator+(const complex &x) // ??
{
    return x;
}

inline complex
operator-(const complex &x)
{
    return complex(-real(x), -imag(x));
}

inline bool
operator==(const complex &left, const complex &right)
{
    return real(left) == real(right) && imag(left) == imag(right);
}

inline bool
operator==(const complex &left, double right)
{
    return real(left) == right && imag(left) == 0;
}

inline bool
operator==(double left, const complex &right)
{
    return left == real(right) && 0 == imag(right);
}

inline bool
operator!=(const complex &left, const complex &right)
{
    return real(left) != real(right) || imag(left) != imag(right);
}

inline bool
operator!=(const complex &left, double right)
{
    return real(left) != right || imag(left) != 0;
}

inline bool
operator!=(double left, const complex &right)
{
    return left != real(right) || 0 == imag(right);
}

inline complex
polar(double r, double t)
{
    return complex(r * cos(t), r * sin(t));
}

inline complex
conj(const complex &x)
{
    return complex(real(x), -imag(x));
}

inline double
norm(const complex &x)
{
    return real(x) * real(x) + imag(x) * imag(x);
}

#endif // !__COMPLEX_H__
```

## comlex_test.cpp 测试

```cpp
#include "complex.h"
#include <iostream>

using namespace std;

ostream &
operator<<(ostream &os, const complex &x)
{
    return os << '(' << real(x) << ',' << imag(x) << ')';
}

int main()
{
    complex c1(2, 1);
    complex c2(4, 0);

    cout << c1 << endl; // (2,1)
    cout << c2 << endl; // (4,0)

    cout << c1 + c2 << endl; // (6,1)
    cout << c1 - c2 << endl; // (-2,1)
    cout << c1 * c2 << endl; // (8,4)
    cout << c1 / 2 << endl;  // (1,0.5)

    cout << conj(c1) << endl;     // (2,-1)
    cout << norm(c1) << endl;     // 5
    cout << polar(10, 4) << endl; // (-6.53644,-7.56802)

    cout << (c1 += c2) << endl; // (6, 1)

    cout << (c1 == c2) << endl; // 0
    cout << (c1 != c2) << endl; // 1
    cout << +c2 << endl;        // (4, 0)
    cout << -c2 << endl;        // (-4, 0)

    cout << (c2 - 2) << endl; // (2, 0)
    cout << (5 + c2) << endl; // (9,0)

    return 0;
}
```


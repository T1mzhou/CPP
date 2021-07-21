# complex类实现

## comlex.h头文件

```cpp
#ifndef __COMPLEX_H__
#define __COMPLEX_H__


class complex;
complex&
    __doapl(complex* ths, const complex& r);
complex&
    __doami(complex* ths, const complex& r);
complex&
    __doaml(complex* ths, const complex& r);


class complex
{
public:
    complex(double r = 0, double i = 0) : re(r), im(i) {}
    complex& operator += (const complex&);
    complex& operator -= (const complex&);
    complex& operator *= (const complex&);
    complex& operator /= (const complex&);
    double real() const { return re; }
    double imag() const { return im; }
private:
    double re, im;

    friend complex& __doapl(complex *, const complex&);
    friend complex& __doami(complex *, const complex&);
    friend complex& __doaml(complex *, const complex&);
};

inline complex&
__doapl(complex* ths, const complex& r)
{
    ths->re += r.re;
    ths->im += r.im;
    return *ths;
}

inline complex&
__doami(complex* ths, const complex& r)
{
    ths->re -= r.re;
    ths->im -= r.im;
    return *ths;
}

inline complex&
__doaml(complex* ths, const complex& r)
{
    double f = ths->re * r.re - ths->im * r.im;
    ths->im = ths->re * r.im + ths->im * r.re;
    ths->re = f;
    return *ths;
}


inline  complex& 
complex::operator += (const complex& r)
{
    return __doapl(this, r);
}

inline  complex& 
complex::operator -= (const complex& r) 
{
    return __doami(this, r);
}

inline  complex& 
complex::operator *= (const complex& r) 
{
    return __doaml(this, r);
}

inline  complex& 
complex::operator /= (const complex& r) 
{
   // todo
}

inline double
real(complex& r) 
{
    return r.real();
}

inline double
imag(complex& i)
{
    return i.imag();
}

inline complex
operator + (const complex& left, const complex& right)
{
    return complex(real(left) + real(right), imag(left) + imag(right));
}

inline complex
operator + (const complex& left, double right)
{
    return complex(real(left) + right, imag(left));
}

inline complex
operator + (double left, const complex& right)
{
    return complex(left + real(right), imag(right));
}



// inline complex&
// complex::operator += (const complex&) {
//     return 
// }
#endif // !__COMPLEX_H__
```


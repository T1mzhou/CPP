#include <iostream>
#include <string>

int main()
{
    double f = 1.53;
    std::string f_str = std::to_string(f);
    std::cout << f_str << '\n';

    double f1 = 4.125;
    std::wstring f_str1 = std::to_wstring(f1);
    std::wcout << f_str1 << '\n';
    
    return 0;
}
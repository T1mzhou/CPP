#include <iostream>
#include <cstdlib>

int main()
{
    const char *str1 = "10";
    const char *str2 = "3.1415";
    const char *str3 = "31337 with words";
    const char *str4 = "words and 2";

    int num1 = std::atoi(str1);
    int num2 = std::atoi(str2);

    int num3 = std::atoi(str3);
    int num4 = std::atoi(str4);
    
    std::cout << "str1" << num1 << std::endl;
    std::cout << "str2" << num2 << std::endl;
    std::cout << "str3" << num3 << std::endl;
    std::cout << "str4" << num4 << std::endl;
    return 0;
}
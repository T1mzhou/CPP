#include <fstream>
#include <iostream>
#include <istream>
#include <iterator>
#include <type_traits>
#include <vector>
#include <string>
#include <algorithm>

int CountLines(const std::string& filename) 
{
    std::fstream in(filename);

    return std::count(std::istreambuf_iterator<char>(in),
                std::istreambuf_iterator<char>(),
                '\n');
}


std::vector<int> CountLineInFiles(const std::vector<std::string>& files)
{
   // return files | std::transform(CountLines);
   return files | std::transform( OpenFile )
                | std::transform( CountLines );
}

int main()
{
    return 0;
}
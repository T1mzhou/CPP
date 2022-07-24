#include <fstream>
#include <iostream>
#include <istream>
#include <iterator>
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


std::vector<int> CountLinesInFiles(const std::vector<std::string>& files)
{
    std::vector<int> res(files.size());

    std::transform(files.cbegin(), files.cend(),
                res.begin(), CountLines);

    return res;
}

int main()
{
    return 0;
}

#include<iostream>
#include<sstream>
#include<string>
#include<algorithm>
#include<iterator>
#include<cmath>
#include<cassert>
#include<array>
#include<vector>
#include<iomanip>
#include<locale>
#include<regex> //regexヘッダで正規表現
#include<optional> //optional(C++17)
#include<ios>
#include<iomanip>
#include<fstream>

#include<experimental/filesystem>

namespace fs = std::experimental::filesystem;

size_t directory_size(fs::path filepath, bool follow_symlink = false)
{
    size_t result = 0;
    fs::recursive_directory_iterator itr;
    if (follow_symlink) {
        itr = fs::recursive_directory_iterator{filepath.native(),fs::directory_options::follow_directory_symlink};
    } else {
        itr = fs::recursive_directory_iterator{filepath.native()};
    }
    for (const fs::directory_entry& x: itr)
    {
        if (!fs::is_directory(x)) result += fs::file_size(x.path());
    }
    return result;
}

int main() 
{
    std::string s;
    std::cin >> s;
    std::cout << directory_size(fs::path(s)) << std::endl;
}

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
#include<chrono>

#include<experimental/filesystem>

namespace fs = std::experimental::filesystem;

std::vector<std::string> match_directory(fs::path const & path, std::regex const & rx)
{
    std::vector<std::string> result;
    for (auto const& entry : fs::recursive_directory_iterator(path))
    {
        //std::cout << fs::path(entry).filename() << std::endl;
        if (std::regex_match(fs::path(entry).filename().c_str(),rx))
        {
            result.push_back(fs::path(entry).string());
        }
    }
    return result;
}

int main() 
{
    std::regex rx(R"([a-zA-Z]{1,5})");
    std::string s;
    std::cin >> s;
    auto res = match_directory(s, rx);
    for (int i = 0; i < res.size(); i++) {
        std::cout << res[i] << std::endl;
    }
}

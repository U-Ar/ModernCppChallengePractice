#include<algorithm>
#include<array>
#include<cassert>
#include<chrono>
#include<cmath>
#include<cstdlib>
#include<ctime>
#include<fstream>
#include<functional>
#include<iomanip>
#include<ios>
#include<iostream>
#include<iterator>
#include<locale>
#include<map>
#include<mutex>
#include<numeric>
#include<sstream>
#include<string>
#include<thread>
#include<utility>
#include<vector>

std::vector<std::string> numbers_in_nation(std::vector<std::string> const & vec,
                                           std::string const & nation)
{
    std::vector<std::string> result(vec.size());
    auto itr = result.begin();
    itr = std::copy_if(std::cbegin(vec),std::cend(vec),itr,[&nation]
    (std::string s){
        if (s[0] == '+') { 
            if (s.substr(1, nation.size()) == nation) return true;
        } else {
            if (s.substr(0,nation.size()) == nation) return true;
        }
        return false;
    });
    result.erase(itr,result.end());
    return result;
}

int main() 
{
    std::vector<std::string> numbers =
    {
        "44-3015085310",
        "+44-1058285",
        "52-1952105",
        "+14-5949"
    };
    for (auto a : numbers_in_nation(numbers,"44"))
    {
        std::cout << a << std::endl;
    }
}
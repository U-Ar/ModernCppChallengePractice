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



bool starts_with(std::string const & num, std::string const & countryCode)
{
    return num.find(countryCode) == 0;
}

template <typename InputIt>
std::vector<std::string> add_nationalid(InputIt begin, InputIt end,
                                       std::string const & countryCode)
{
    std::vector<std::string> result(0);
    for (InputIt itr=begin; itr != end; itr++)
    {
        std::string tmp = *itr;
        if (!starts_with(tmp,"+"+countryCode)) 
        {
            if (!starts_with(tmp,countryCode)) tmp = "+"+countryCode+tmp;
            else tmp = "+"+tmp;
        }
        tmp.erase(std::remove_if(tmp.begin(),tmp.end(),[](char const c){return c == ' ';}),tmp.end());
        result.push_back(tmp);
    }
    return result;
}

std::vector<std::string> add_nationalid(std::vector<std::string> const & vec,
                                       std::string const & countryCode)
{
    return add_nationalid(std::begin(vec),std::end(vec),countryCode);
}

int main() 
{
    std::vector<std::string> numbers =
    {
        "07555 123456",
        "07555123456",
        "+44 7555123456",
        "44 75 123455",
        "7555 123455"
    };
    for (auto a : add_nationalid(numbers,"44"))
    {
        std::cout << a << std::endl;
    }
}

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

template<typename InputIt>
std::vector<std::string> filter_number(InputIt begin, InputIt end,
                                       std::string const & countryCode)
{
    std::vector<std::string> result;
    std::copy_if(begin, end, std::back_inserter(result),
    [&countryCode](std::string const & num) {
        return starts_with(num,countryCode) || 
               starts_with(num, "+" + countryCode);
    });
    return result;
}

std::vector<std::string> filter_number(std::vector<std::string> const & vec,
                                       std::string const & countryCode)
{
    return filter_number(std::cbegin(vec),std::cend(vec),countryCode);
}

int main() 
{
    std::vector<std::string> numbers =
    {
        "44-3015085310",
        "+44-1058285",
        "52-1952105",
        "+14-5949",
        "7593230"
    };
    for (auto a : filter_number(numbers,"44"))
    {
        std::cout << a << std::endl;
    }
}
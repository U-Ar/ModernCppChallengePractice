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
#include<ctime>
#include<functional>
#include<thread>
#include<cstdlib>
//#include<filesystem>

#include"date/date.h"

namespace ch = std::chrono;

inline int number_of_days(
    int const y1, unsigned int const m1, unsigned int const d1,
    int const y2, unsigned int const m2, unsigned int const d2
)
{
    using namespace date;
    return (sys_days{year{y1}/month{m1}/day{d1}} -
            sys_days{year{y2}/month{m2}/day{d2}}).count();
}

inline int number_of_days(date::sys_days const & first,
date::sys_days const & second)
{
    return (second-first).count();
}

int main() 
{
    auto diff1 =  number_of_days(2016,9,23,2017,5,15);
    using namespace date::literals;
    auto diff2 = number_of_days(2016_y/sep/23, 15_d/may/2017);
    std::cout << diff1 << " " << diff2 << std::endl;
}

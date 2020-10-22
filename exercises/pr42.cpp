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

inline int date_to_nthday(
    int const y1, unsigned int const m1, unsigned int const d1
)
{
    using namespace date;
    return (sys_days{year{y1}/month{m1}/day{d1}} -
            sys_days{year{y1-1}/month{12}/day{31}}).count();
}

inline int date_to_nthweek(
    int const y1, unsigned int const m1, unsigned int const d1
)
{
    using namespace date;
    return (sys_days{year{y1}/month{m1}/day{d1}} -
            sys_days{year{y1}/month{1}/day{1}}).count()/7+1;
}

int main() 
{
    auto d = date_to_nthweek(2019,4,21);
    std::cout << d << std::endl;
}

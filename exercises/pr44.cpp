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
#include"date/iso_week.h"

namespace ch = std::chrono;

void print_calender(int const y, int const m)
{
    using namespace date;
    std::cout << "Mon Tue Wed Thu Fri Sat Sun" << std::endl;
    auto const dt = year_month_day{ year{y}, month{m}, day{1} };
    unsigned int wn = static_cast<unsigned int>(iso_week::year_weeknum_weekday{dt}.weekday());
    day d = year_month_day_last{ year{y}, month_day_last{m / last} }.day();
    unsigned int dl = static_cast<unsigned int>(d);
    for (unsigned int i = 1; i < wn; i++) std::cout << "    ";
    for (unsigned int i = 1; i <= dl; i++)
    {
        std::cout << std::right << std::setfill(' ') << std::setw(3)
        << i << ' ';
        wn++;
        if (wn == 8) {
            wn = 1; std::cout << std::endl;
        }
    }
    std::cout << std::endl;
}

int main() 
{
    std::cout << "input year and month:" << std::endl;
    int a, b; std::cin >> a >> b;
    print_calender(a, b);
}

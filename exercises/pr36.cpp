
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
namespace ch = std::chrono;

//chronoの使い方がいまいち

void remove_older(fs::path const & filepath, ch::system_clock::timepoint const & time)
{
    fs::recursive_directory_iterator itr{filepath.native()};
    for (fs::directory_entry& x: itr)
    {
        if (fs::last_write_time(x) <= time) {
            fs::remove(x.path())
        }
    }    
}

int main() 
{
    int day, time, minute, second;
    std::cout << "Type Day&time&minute&second" << std::endl;
    std::cin >> day >> hour >> minute >> second;

    ch::system_clock::timepoint now = system_clock::now();
    ch::system_clock::timepoint old = now - ch.seconds(second)
    - ch.minutes(minute) - ch.hours(hour) - ch.days(day);

    std::cout << remove_older(fs::path(s), old) << std::endl;

    
}


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

enum class procstatus {suspended, running};
enum class platforms {p32bit, p64bit};

struct procinfo {
    int id;
    std::string name;
    procstatus status;
    std::string account;
    size_t memory;
    platforms platform;
}

std::string status_to_string(procstatus const status)
{
    if (status == procstatus::suspended)
    return "Suspended";
    return "Running";
}

std::string platform_to_string(platforms const platform)
{
    if (platform == platforms::p32bit)
    return "32-bit";
    return "64-bit";
}

void print_processes(std::vector<procinfo> processes)
{
    std::sort(std::begin(processes), std::end(processes),
    [](procinfo const & p1, procinfo const & p2) {
        return p1.name < p2.name;
    });
    for (auto const & pi : processes)
    {
        std::cout << std::left << std::setw(25) << std::setfill(' ')
        <<pi.name;
    }
}

int main() 
{
    
}

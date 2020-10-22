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
#include<functional>
#include<thread>

//#include<filesystem>

namespace ch = std::chrono;

template <typename Time = std::chrono::microseconds,
          typename Clock = std::chrono::high_resolution_clock>
struct perf_timer 
{
    template <typename F, typename... Args> 
    static Time duration(F&& f, Args... args)
    {
        auto start = Clock::now();
        std::invoke(std::forward<F>(f), std::forward<Args>(args)...);
        auto end = Clock::now();

        return std::chrono::duration_cast<Time>(end-start);
    }
};

using namespace std::chrono_literals;

void f()
{
    std::this_thread::sleep_for(2s);
}

void g(const int a, const int b)
{
    std::this_thread::sleep_for(1s);
}


int main() 
{
    std::cout << perf_timer<std::chrono::microseconds>::duration(f).count() << " " <<
    perf_timer<std::chrono::milliseconds>::duration(g,4,3).count() << std::endl;
}

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

#include<filesystem>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/uuid_generators.hpp> // random_generator

namespace ch = std::chrono;
using namespace boost::uuids;

template<typename Duration, typename Func, typename... Args>
Duration execution_time(Func const & func, Args&&... args)
{
    auto start = ch::system_clock::now().time_since_epoch();
    func(args...);
    auto end = ch::system_clock::now().time_since_epoch();
    return ch::duration_cast<Duration>(end-start);
}

void f1(int a, int b, int c)
{
    a = b + c;
    for (int i = 0; i < 100000; i++) {
        b++;
    }
}

int main() 
{
    using namespace std::chrono_literals;
    std::cout << execution_time<ch::seconds>(f1, 3, 2, 1) << std::endl;
}

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

template<class T>
std::vector<std::pair<T,size_t> > find_most_frequent(std::vector<T> const & range)
{
    std::map<T, size_t> counts;

    for (auto const& e : range) counts[e]++;

    auto maxelem = std::max_element(
        std::cbegin(counts), std::cend(counts), 
        [](auto const & e1, auto const & e2) {
            return e1.second < e2.second; 
        }
    );

    std::vector<std::pair<T,size_t> > result;

    std::copy_if(
        std::cbegin(counts), std::cend(counts), 
        std::back_inserter(result), 
        [maxelem](auto const & kvp) {
            return kvp.second == maxelem->second;
        }
    );

    return result;
}

int main() 
{
    auto range = std::vector<int> {1,1,3,5,8,13,3,5,8,8,5};
    auto result = find_most_frequent(range);

    for (auto const & [a,b] : result)
    {
        std::cout << a << ":" << b << " ";
    }
    std::cout << std::endl;
}
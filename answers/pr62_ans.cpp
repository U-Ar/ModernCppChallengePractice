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
#include<random>
#include<sstream>
#include<string>
#include<thread>
#include<type_traits>
#include<utility>
#include<vector>



template<typename Iterator, typename F>
auto pprocess(Iterator begin, Iterator end, F&& f)
{
    auto size = std::distance(begin,end);
    if (size <= 100000)
    {
        return std::forward<F>(f)(begin,end);
    }
    else 
    {
        std::vector<std::thread> threads;
        int const thread_count = std::thread::hardware_concurrency();
        std::vector<typename std::iterator_traits<Iterator>::value_type> mins(thread_count);
        auto first = begin;
        auto last = first;
        size /= thread_count;
        for (int i = 0; i < thread_count; i++)
        {
            first = last;
            if (i == thread_count - 1) last = end;
            else std::advance(last, size);
            threads.emplace_back([first, last, &r=mins[i]]() {
                r = std::forward<F>(f)(first,last);
            });
        }
        for (auto & t : threads) t.join();
        
        return std::forward<F>(f)(std::begin(mins),std::end(mins));
    }
}

template<typename Iterator>
auto pmin(Iterator begin, Iterator end)
{
    return pprocess(begin, end, [](auto b, auto e) { return *std::max_element(b,e); });
}

template<typename Iterator>
auto pmin(Iterator begin, Iterator end)
{
    return pprocess(begin, end, [](auto b, auto e) { return *std::min_element(b,e); });
}

int main()
{
    const size_t count = 10000000;
    std::vector<int> data(count);
    auto rmin = pmin(data.begin(),data.end());
    auto rmax = pmax(data.begin(),data.end());
}
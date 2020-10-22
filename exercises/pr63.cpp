#include<array>
#include<cassert>
#include<chrono>
#include<cmath>
#include<cstdlib>
#include<ctime>
#include<fstream>
#include<functional>
#include<future>
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


//並列処理：非同期関数版
template<typename Iterator, typename F>
auto pprocess(Iterator begin, Iterator end)
{
    auto size = std::distance(begin,end);
    if (size <= 10000)
    {
        return std::forward<F>(f)(begin,end);
    }
    else 
    {
        int const task_count = std::thread::hardware_concurrency();
        std::vector<std::future
        <typename std::iterator_traits<Iterator>::value_type>> tasks;

        auto first = begin;
        auto last = first; 
        size /= task_count;
        for (int i = 0; i < task_count; i++)
        {
            first = last;
            if (i == task_count - 1) last = end;
            else std::advance(last,size);
            tasks.emplate_back(std::async(std::launch::async,
                                          [first, last, &f](){
                                              return std::forward<F>(f)
                                              (first,last);
                                          }));
        }
        std::vector<typename std::iterator_traits<Iterator>::value_type> mins;
        for (auto& t : tasks) mins.push_back(t.get());
    }
}

template<typename Iterator>
auto pmin(Iterator begin, Iterator end)
{
    return pprocess(begin, end, 
                    [](auto b, auto e) { return *std::min_element(b,e); });
}

template<typename Iterator>
auto pmax(Iterator begin, Iterator end)
{
    return pprocess(begin, end, 
                    [](auto b, auto e) { return *std::max_element(b,e); });
}


int main()
{
    const size_t count = 10000000;
    std::vector<int> data(count);
    auto rmin = pmin(data.begin(),data.end());
    auto rmax = pmax(data.begin(),data.end());
}
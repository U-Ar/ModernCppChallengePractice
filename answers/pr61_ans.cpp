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


template<typename RandomAccessIterator, typename F>
void ptransform(RandomAccessIterator begin, RandomAccessIterator end,
                F&& f)
{
    auto size = std::distance(begin,end);
    if (size <= 1000000)
    {
        std::transform(begin, end, begin, std::forward<F>(f));
    }
    else 
    {
        std::vector<std::thread> threads;
        int const thread_count = std::thread::hardware_concurrency();
        auto first = begin;
        auto last = first;
        size /= thread_count;
        for (int i = 0; i < thread_count; i++)
        {
            first = last;
            if (i == thread_count - 1) last = end;
            else std::advance(last, size);
            threads.emplace_back([first, last, &f]() {
                std::transform(first,last,first,std::forward<F>(f));
            });
        }
        for (auto & t : threads) t.join();
    }
}

template<typename T, typename F>
std::vector<T> palter(std::vector<T> data, F&& f)
{
    ptransform(std::begin(data), std::end(data), std::forward<F>(f));
    return data;
}

int main()
{
    auto past = std::chrono::high_resolution_clock::now();
    std::vector<int> data(1000);
    palter(data, [](int const e) { return e * e; });
    auto now = std::chrono::high_resolution_clock::now();
    std::cout << 
    std::chrono::duration_cast<std::chrono::microseconds>(now-past).count()
    << std::endl;

    past = std::chrono::high_resolution_clock::now();
    std::vector<int> data2(10000);
    palter(data2, [](int const e) { return e * e; });
    now = std::chrono::high_resolution_clock::now();
    std::cout << 
    std::chrono::duration_cast<std::chrono::microseconds>(now-past).count()
    << std::endl;

    past = std::chrono::high_resolution_clock::now();
    std::vector<int> data3(100000);
    palter(data3, [](int const e) { return e * e; });
    now = std::chrono::high_resolution_clock::now();
    std::cout << 
    std::chrono::duration_cast<std::chrono::microseconds>(now-past).count()
    << std::endl;

    past = std::chrono::high_resolution_clock::now();
    std::vector<int> data4(1000000);
    palter(data4, [](int const e) { return e * e; });
    now = std::chrono::high_resolution_clock::now();
    std::cout << 
    std::chrono::duration_cast<std::chrono::microseconds>(now-past).count()
    << std::endl;

    past = std::chrono::high_resolution_clock::now();
    std::vector<int> data5(10000000);
    palter(data5, [](int const e) { return e * e; });
    now = std::chrono::high_resolution_clock::now();
    std::cout << 
    std::chrono::duration_cast<std::chrono::microseconds>(now-past).count()
    << std::endl;
}
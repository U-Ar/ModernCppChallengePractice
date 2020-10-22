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



template<typename RandomAccessIterator, typename T = typename RandomAccessIterator::value_type>
T pmax_element(RandomAccessIterator begin, RandomAccessIterator end)
{
    auto size = std::distance(begin,end);
    if (size <= 100000)
    {
        return *std::max_element(begin,end);
    }
    else 
    {
        std::vector<std::thread> threads;
        int const thread_count = std::thread::hardware_concurrency();
        T result = std::numeric_limits<T>::min();
        auto first = begin;
        auto last = first;
        size /= thread_count;
        for (int i = 0; i < thread_count; i++)
        {
            first = last;
            if (i == thread_count - 1) last = end;
            else std::advance(last, size);
            threads.emplace_back([first, last, &result]() {
                result = std::max(result, 
                         *std::max_element(first, last));
            });
        }
        for (auto & t : threads) t.join();
        return result;
    }
}

int main()
{
    std::vector<int> vec(1000000);
    for (int i = 0; i < 1000000; i++) vec[i] = i;
    std::cout << pmax_element(vec.begin(),vec.end()) << std::endl;
}
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

template<typename RandomIt>
RandomIt partition(RandomIt first, RandomIt last)
{
    auto pivot = *first;
    auto i = first+1;
    auto j = last-1;
    while (i <= j)
    {
        while (i <= j && *i <= pivot) i++;
        while (i <= j && *j > pivot)  j--;
        if (i < j) std::iter_swap(i,j);
    }
    std::iter_swap(i-1,first);
    return i-1;
}

template<typename RandomIt>
void quicksort(RandomIt first, RandomIt last)
{
    if (first < last)
    {
        auto p = partition(first, last);
        quicksort(first, p);
        quicksort(p+1, last);
    }
}

template<typename Iterator>
void pquicksort(Iterator begin, Iterator end)
{
    int dist = std::distance(begin,end);
    if (dist <= 100)
    {
        quicksort(begin,end);
    }
    else
    {
        int threads = std::thread::hardware_concurrency();
        int k = 1;
        while ((1 << (k+1)) <= threads) k++;

        std::vector<Iterator> its {begin, end};
        std::vector<std::thread> ths;

        for (int i = 0; i < k; i++)
        {
            for (int j = 0; j < (1<<i); j++)
            {
                auto p = partition(its[2*j],its[2*j+1]);
                its.insert(its.begin()+1+2*j, p);
            }
        }
        for (size_t i = 0; i < its.size()-1; i++)
        {
            ths.emplace_back([i,&its](){ 
                quicksort(its[i],its[i+1]); });
        }
        for (auto& t : ths) t.join();
    }
}


int main()
{
    std::vector<int> a(400);
    for (size_t i = 0; i < 200; i++)
    {
        a[i] = 200 - i;
    }
    for (size_t i = 200; i < 400; i++)
    {
        a[i] = i - 400;
    }


    pquicksort(a.begin(),a.end());
    for (auto x : a)
    {
        std::cout << x << " ";
    }
    std::cout << std::endl;
}
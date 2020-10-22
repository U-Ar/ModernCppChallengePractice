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
    if (begin < end)
    {
        auto const p = partition(begin, end);

        if (std::distance(begin,end) <= 100000)
        {
            pquicksort(begin, p);
            pquicksort(p+1,end);
        }
        else
        {
            auto f1 = std::async(std::launch::async,
            [begin,p](){ pquicksort(begin, p); });
            auto f2 = std::async(std::launch::async,
            [end,p]() { pquicksort(p+1,end); });
            f1.wait();
            f2.wait();
        }       
    }
}

int main()
{
    namespace ch = std::chrono;

    std::vector<int> a(1000000), b(1000000);
    for (size_t i = 0; i < a.size(); i++) a[i] = b[i] = std::min(i,a.size()-i);

    auto t1 = ch::high_resolution_clock::now();
    quicksort(a.begin(),a.end());
    auto t2 = ch::high_resolution_clock::now();
    std::cout << "山形データ サイズ" << a.size() << " 非並列版\n";
    std::cout << ch::duration_cast<ch::milliseconds>(t2-t1).count() << std::endl;

    t1 = ch::high_resolution_clock::now();
    pquicksort(b.begin(),b.end());
    t2 = ch::high_resolution_clock::now();
    std::cout << "山形データ サイズ" << b.size() << " 並列版\n";
    std::cout << ch::duration_cast<ch::milliseconds>(t2-t1).count() << std::endl;


    b.resize(20000);
    for (size_t i = 0; i < b.size(); i++) b[i] = b.size() - i;
    t1 = ch::high_resolution_clock::now();
    quicksort(b.begin(),b.end());
    t2 = ch::high_resolution_clock::now();
    std::cout << "降順データ サイズ" << b.size() << " 非並列版\n";
    std::cout << ch::duration_cast<ch::milliseconds>(t2-t1).count() << std::endl;

    for (size_t i = 0; i < b.size(); i++) b[i] = b.size() - i;
    t1 = ch::high_resolution_clock::now();
    pquicksort(b.begin(),b.end());
    t2 = ch::high_resolution_clock::now();
    std::cout << "降順データ サイズ" << b.size() << " 並列版\n";
    std::cout << ch::duration_cast<ch::milliseconds>(t2-t1).count() << std::endl;

}
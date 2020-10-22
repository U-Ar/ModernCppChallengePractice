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
#include<type_traits>
#include<utility>
#include<vector>

template<typename Iterator>
void quicksort(Iterator begin, Iterator end)
{
    using T = typename std::iterator_traits<Iterator>::value_type;
    if ((end-begin) <= 1) return;
    T pivot = *(begin);
    Iterator left = begin+1, right = end-1;
    while (left <= right)
    {
        while (left <= right && *left <= pivot) left++;
        while (left <= right && pivot <= *right) right--;
        if (left < right) {
            std::iter_swap(left,right);
            left++; right--;
        } 
    }
    std::iter_swap(begin, left-1);
    quicksort<Iterator>(begin, left-1);
    quicksort<Iterator>(left, end);
}

template<typename Iterator, typename Comp>
void quicksort(Iterator begin, Iterator end, Comp comp)
{
    using T = typename std::iterator_traits<Iterator>::value_type;
    if ((end-begin) <= 1) return;
    T pivot = *(begin);
    Iterator left = begin+1, right = end-1;
    while (left <= right)
    {
        while (left <= right && comp(*left,pivot)) left++;
        while (left <= right && comp(pivot,*right)) right--;
        if (left < right) {
            std::iter_swap(left,right);
            left++; right--;
        } 
    }
    std::iter_swap(begin, left-1);
    quicksort<Iterator,Comp>(begin, left-1, comp);
    quicksort<Iterator,Comp>(left, end, comp);
}

int main() 
{
    std::vector<int> a {10,1,9,2,8,3,8,4,7,5,7,6};
    quicksort(a.begin(),a.end());
    for (auto x : a) std::cout << x << " ";
    std::cout << std::endl;

    a = {10,1,9,2,8,3,8,4,7,5,7,6};
    quicksort(a.begin(),a.end(),std::greater_equal<int>());
    for (auto x : a) std::cout << x << " ";
    std::cout << std::endl;
}

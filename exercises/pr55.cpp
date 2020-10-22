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

template<typename I1, typename I2, typename Output>
void zip(I1 const begin1, I1 const end1,
         I2 const begin2, I2 const end2, Output result)
{
    I1 it1 = begin1;
    I2 it2 = begin2;
    while (it1 != end1 && it2 != end2)
    {
        result++ = std::make_pair(*it1++,*it2++);
    }
}

template<typename T, typename U>
std::vector<std::pair<T, U> > zip(std::vector<T> const& a,
                             std::vector<U> const& b)
{
    std::vector<std::pair<T,U> > result;
    zip(a.cbegin(),a.cend(),b.cbegin(),b.cend(),std::back_inserter(result));
    return result;
}

int main() 
{
    std::vector<int> a = {1,2,3};
    std::vector<std::string> b = {"a", "gsx", "aig"};
    for (auto [x,y] : zip(a,b))
    {
        std::cout << x << " " << y << std::endl;
    }
}

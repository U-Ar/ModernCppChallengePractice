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

template<typename T>
std::vector<std::pair<T,T> > make_pairs(std::vector<T> const& vec)
{
    std::vector<std::pair<T,T> > result(0);
    for (size_t i = 1; i < vec.size(); i+=2)
    {
        result.push_back(std::make_pair(vec[i-1],vec[i]));
    }
    return result;
}


int main() 
{
    auto v = make_pairs(std::vector<int>{1,1,3,5,8,13,21});
    for (auto p : v)
    {
        std::cout << p.first << ":" << p.second << std::endl;
    }

}

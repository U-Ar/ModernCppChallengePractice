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
bool compare(std::pair<T,int> const & a, std::pair<T,int> const & b)
{
    return a.second >= b.second;
}

template<class T>
std::vector<std::pair<T, int> > most_frequent_elements(std::vector<T> const& vec)
{
    std::vector<std::pair<T, int> > result(0);
    std::map<T, int> mp;
    //record frequency to map
    for (auto x : vec) mp[x] += 1;
    for (auto x : mp) result.push_back(x);
    //sort pairs based on frequency
    std::sort(result.begin(),result.end(),compare<T>);
    size_t i = 0;
    while (i < result.size() && result[i].second == result[0].second) i++;
    //erase not most frequent elements
    if (i < result.size()) result.erase(result.begin()+i,result.end());
    return result;
}

template<class T>
void print_vec(std::vector<std::pair<T, int> > const & vec)
{
    for (auto x : vec) std::cout << "(" << x.first << "," << x.second 
                                 << ")" << " ";
    std::cout << std::endl;
}

int main() 
{
    print_vec(most_frequent_elements(std::vector<int>{1,1,3,5,8,12,3,5,8,8,5}));
}
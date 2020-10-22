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

template<typename C, typename Func>
void transform(C& container, Func func)
{
    size_t n = std::thread::hardware_concurrency(); 
    std::vector<std::thread> threads(n);
    size_t p = container.size()/n;
    for (size_t i = 0; i < n; i++)
    {
        threads[i] = std::thread([&]{ 
            for (size_t j = i*p; 
                 j < std::min(container.size(),(i+1)*p);
                 j++) container[j] = func(container[j]);
        });
    } 
    for (auto& t : threads) t.join();
}

int plus(int a) { return a + 1; }

int main()
{
    std::vector<int> a(200,0);
    transform(a, plus);
    for (auto x : a) std::cout << x << " ";
    std::cout << std::endl;
}
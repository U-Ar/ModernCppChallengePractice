#include<cassert>
#include<chrono>
#include<cmath>
#include<cstdlib>
#include<ctime>
#include<cctype>
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
#include<set>
#include<sstream>
#include<string>
#include<thread>
#include<type_traits>
#include<utility>
#include<vector>

void print_now()
{
    auto now = std::chrono::system_clock::now();
    time_t t = std::chrono::system_clock::to_time_t(now);
    const tm* lt = std::localtime(&t);
    std::cout << std::put_time(lt, "%c");
}

template<class T>
class Vector 
{
    std::vector<T> data;
public:
    Vector() : data(0) {}
    explicit Vector(std::vector<T> const& vec) : data(vec) {}
    explicit Vector(std::initializer_list<T> init)
    : data(init.begin(),init.end()) {}
    explicit Vector(size_t const size, T const & x)
    : data(size, x) {}
    explicit Vector(typename std::vector<T>::iterator begin,
                    typename std::vector<T>::iterator end)
    : data(begin,end) {}
    
    Vector& operator=(Vector const& other)
    {
        data = other.data;
        std::cout << "substituted at " ;
        print_now();
        std::cout << std::endl;
        std::cout << "new size: " << data.size() << std::endl << std::endl;

        return *this;
    }

    void push_back(T const& x)
    {
        data.push_back(x);
        std::cout << "added at "; 
        print_now();
        std::cout << std::endl;
        std::cout << "added index: " << data.size()-1 << std::endl << std::endl;
    }

    void pop_back()
    {
        std::cout << "removed at "; 
        print_now();
        std::cout << std::endl;
        std::cout << "removed index: " << data.size()-1 << std::endl << std::endl;
        data.pop_back();
    }

    void clear()
    {
        data.clear();
        std::cout << "cleared at "; 
        print_now();
        std::cout << std::endl << std::endl;
    }

    size_t size() const noexcept
    {
        return data.size();
    }

    bool empty() const noexcept 
    {
        return data.empty();
    }

    typename std::vector<T>::iterator begin() { return data.begin(); }
    typename std::vector<T>::iterator end() { return data.end(); }
    typename std::vector<T>::const_iterator cbegin() const 
    { return data.cbegin(); }
    typename std::vector<T>::const_iterator cend() const 
    { return data.cend(); }       
};

int main() 
{
    Vector<int> a({1,2,3,4,5,6});
    a.push_back(10);
    a.pop_back();
    a.pop_back();

    a.clear();

    a = Vector<int>{4,3,2,1};
    
}
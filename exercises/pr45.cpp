#include<iostream>
#include<sstream>
#include<string>
#include<algorithm>
#include<iterator>
#include<cmath>
#include<cassert>
#include<array>
#include<vector>
#include<iomanip>
#include<locale>
#include<ios>
#include<iomanip>
#include<fstream>
#include<chrono>
#include<ctime>
#include<functional>
#include<utility>
#include<cstdlib>


template<typename T, 
         typename Comp = std::less<T> >
class pr_queue 
{
    std::vector<T> data;
    Comp comparer;
public:
    constexpr pr_queue() : data(0) {}
    explicit constexpr pr_queue(std::vector<T> const & v) 
    {
        data = v;
        for (size_t i = (data.size()-1)/2+1; i > 0; i--)
        {
            this->heapify(i-1);
        }
    }
    ~pr_queue() noexcept {}

    constexpr T* data_() noexcept { return data.data(); }
    constexpr T const * data_() const noexcept { return data.data(); }
    constexpr size_t const size() const noexcept { return data.size(); }
    constexpr bool const empty() const noexcept { return data.size() == 0; }

    void heapify(size_t const a) 
    {
        if (data.size() == 0) throw std::out_of_range("This que has no components");
        if (a >= data.size()) throw std::out_of_range("Invalid index");
        size_t i = a, l = i, r = i;
        while (true)
        {
            l = 2*(i+1)-1; r = 2*(i+1);
            if (l >= data.size()) return;
            else if (r >= data.size()) 
            {
                if (comparer(data[i],data[l])) return;
                std::swap(data[i], data[l]);
                i = l;
            }
            else
            {
                i = comparer(data[l],data[r]) ? 
                        l : r;
                if (comparer(data[(i+1)/2-1],data[i])) return;
                
                std::swap(data[(i+1)/2-1], data[i]);
            }
        }
    }
    
    constexpr T const top() const 
    {
        if (data.size() == 0) throw std::out_of_range("This queue has no elements");
        return data[0]; 
    }

    void pop() 
    {
        for (auto a : data)
        {
            std::cout << a << " ";
        } std::cout << std::endl;
        size_t l = data.size();
        if (l == 0) throw std::out_of_range("This queue has no elements");
        std::swap(data[0],data[l-1]);
        data.erase(data.end()-1);
        this->heapify(0);   
    }

    void push(T const a)
    {
        data.insert(data.end(),a);
        size_t i = data.size()-1;
        while (true)
        {
            if (i == 0 || comparer(data[(i+1)/2-1], data[i])) break;
            std::swap(data[(i+1)/2-1], data[i]);
            i = (i+1)/2-1;
        }
    }

    void print()
    {
        for (auto a : data)
        {
            std::cout << a << " ";
        } std::cout << std::endl;
    }
};

int main() 
{
    std::vector<int> a = {5, 4, 8, 7, 1, 2, 3, 6, 9};
    pr_queue<int> que(a);
    std::cout << que.top() << std::endl;
    que.print();
    que.pop();
    que.pop();
    que.pop();
    std::cout << que.top() << std::endl;
}

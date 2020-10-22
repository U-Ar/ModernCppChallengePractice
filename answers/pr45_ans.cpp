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


template<class T, 
class Compare = std::less<typename std::vector<T>::value_type> >
class priority_queue
{
    typedef typename std::vector<T>::value_type value_type;
    typedef typename std::vector<T>::size_type  size_type;
    typedef typename std::vector<T>::reference  reference;
    typedef typename std::vector<T>::const_reference const_reference;
private: 
    std::vector<T> data;
    //テンプレートパラメータに関数オブジェクトを指定した場合
    //それは関数の「型」でしかないので具体的なオブジェクトを作る
    Compare comparer;
public:
    bool empty() const noexcept { return data.empty(); }
    size_type size() const noexcept { return data.size(); }
    
    void push(value_type const & value)
    {
        data.push_back(value);
        std::push_heap(std::begin(data),std::end(data),comparer);
    }

    void pop()
    {
        std::pop_heap(std::begin(data),std::end(data),comparer);
        data.pop_back();
    }

    const_reference top() const { return data.front(); }
    void swap(priority_queue& other) noexcept 
    {
        swap(data, other.data);
        swap(comparer, other.comparer);
    }
}

template <class T, class Compare>
void swap(priority_queue<T, Compare> & lhs, 
          priority_queue<T, Compare> & rhs)
          noexcept(noexcept(lhs.swap(rhs)))
          //lhs.swapが例外を送出しない場合、swapもまた例外を送出しない
{
    lhs.swap(rhs);
}

int main() 
{
}

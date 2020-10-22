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



template<class T, size_t N>
class ring_buffer
{
private:
    std::array<T,N> data;
    size_t size_;
public:
    ring_buffer() = delete;
    explicit constexpr ring_buffer(std::array<T,N> const & d) : data(d), size_(N) {}
    explicit constexpr ring_buffer(std::vector<T> const & d) 
    {
        if (N < d.size()) throw std::invalid_argument("Different length");
        for (size_t i = 0; i < d.size(); i++) data[i] = d[i];
        size_ = d.size();
    }

    constexpr bool empty() const { return data.empty(); }
    constexpr bool full() const { return size_ == N; }
    constexpr size_t size() const { return size_; }
    constexpr size_t capacity() const { return N - size_; }

    constexpr void push(T const & a)
    {
        if (size_ < N) size_++;
        for (long long int i = size_ - 2; i >= 0; i--)
        {
            data[i+1] = data[i];
        }
        data[0] = a;
    }

    constexpr void pop()
    {
        size_--;
    }

    T const * begin() const { return data.data(); }
    T const * end()   const { return data.data() + size_; }
    T * begin()             { return data.data(); }
    T * end()               { return data.data() + size_; }

    void swap(ring_buffer& other)
    {
        swap(data, other.data);
        swap(size_, other.size_);
    }

    void print()
    {
        for (size_t i = 0; i < size_; i++)
        {
            std::cout << data[i] << " ";
        } std::cout << std::endl;
    }
};

template <class T, size_t N>
void swap(ring_buffer<T, N> & lhs, 
          ring_buffer<T, N> & rhs)
          noexcept(noexcept(lhs.swap(rhs))) //lhs.swapが例外を送出しない場合、swapもまた例外を送出しない
{
    lhs.swap(rhs);
}

int main() 
{
    ring_buffer<int, 10> buf(std::vector<int>{1,2,3});
    buf.print();
    buf.push(4);
    buf.push(5);
    buf.print();
    buf.pop();
    buf.pop();
    buf.print();
    for (int i = 10; i > 5; i--) buf.push(i);
    for (auto a : buf){
        std::cout << a << " "; 
    }
}

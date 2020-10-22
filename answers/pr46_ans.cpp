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

template<class T>
class circular_buffer;

template<class T>
class circular_buffer_iterator
{
    //イテレータに必要なデータ群
    using self_type         = circular_buffer_iterator;
    using value_type        = T;
    using reference         = T&;
    using const_reference   = T const&;
    using pointer           = T*;
    using const_pointer     = T const*;
    using iterator_category = std::random_access_iterator_tag;
    using difference_type   = ptrdiff_t;

private:    
    circular_buffer<T> const & buffer_; //リングバッファ本体の参照
    size_t index_; //インデックス
    bool last_; //最後の要素かのフラッグ

    bool compatible(self_type const& other) const
    {
        return &buffer_ == &other.buffer_;
    }

public:
    circular_buffer_iterator(circular_buffer<T> const & buf, 
        size_t const pos, bool const last)
        : buffer_(buf), index_(pos), last_(last) {}
    
    //前置インクリメント
    self_type & operator++()
    {
        if (last_)
            throw std::out_of_range("Iterator cannot be incremented.");
        index_ = (index_ + 1) % buffer_.data_.size();
        last_ = index_ == buffer_.next_pos();
        return *this;
    }
    //後置インクリメント
    self_type operator++(int)
    {
        self_type itr = *this;
        ++(*this);
        return itr;
    }

    bool operator==(self_type const & other) const 
    {
        assert(compatible(other));
        return (index_ == other.index_) && (last_ == other.last_);
    }

    bool operator!=(self_type const & other) const 
    {
        return !(*this == other);
    }

    const_reference operator*() const
    {
        return buffer_.data_[index_];
    }

    const_pointer operator->() const 
    {
        return std::addressof(operator*());
    }
};


template<class T>
class circular_buffer
{
    using const_iterator = circular_buffer_iterator<T>;

private:
    std::vector<T> data_;
    size_t head_ = -1;
    size_t size_ = 0;

    size_t next_pos() const noexcept 
    { return size_ == 0 ? 0 : (head_ + 1) % data_.size(); }

    size_t first_pos() const noexcept 
    { return size_ == 0 ?
    0 : (head_ + data_.size() - size_ + 1) % data_.size(); }

    friend class circular_buffer_iterator<T>;

public:
    circular_buffer() = delete; //デフォルトコンストラクタの禁止
    explicit circular_buffer(size_t const size) : data_(size) {}

    void clear() noexcept { head_ = -1; size_ = 0; }

    bool empty() const noexcept { return size_ == 0; }
    bool full() const { return size_ == data_.size(); }
    size_t size() const { return size_; }
    size_t capacity() const { return data_.size(); }

    void push(T const item)
    {
        head_ = next_pos();
        data_[head_] = item;
        if (size_ < data_.size()) size_++;
    }

    T pop()
    {
        if (empty()) throw std::runtime_error("empty buffer");
        size_t pos = first_pos();
        size_--;
        return data_[pos];
    }

    //イテレータ用操作の定義　実体として返すのはcircular_buffer_iterator
    const_iterator begin() const
    {
        return const_iterator(*this, first_pos(), empty());
    }

    const_iterator end() const
    {
        return const_iterator(*this, next_pos(), true);
    }
};


int main() 
{
    circular_buffer<int> buf(5);
    buf.push(1);
    buf.push(2);
    for (auto a = buf.begin(); a != buf.end(); a++) std::cout << *a << " ";
    std::cout << std::endl;

    buf.push(3);
    buf.push(4);
    buf.push(5);
    buf.push(6);
    for (auto a = buf.begin(); a != buf.end(); a++) std::cout << *a << " ";
    std::cout << std::endl;

}

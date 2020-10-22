//pr47.cpp

/*
要求された機能を実装するには、バッファクラスに内部バッファが2つ必要
1つは書き込まれる一時データを含み、もう1つは、完全なデータを含む
書き出し演算が完了すると、一時バッファの内容が永続バッファに書き出される。
内部バッファに関してはvectorを用いる。
書き込みが完了したら、2つのバッファをスワップする
アクセスは[]かread()によるコピー
バッファへのアクセスはstd::mutexで同期を取り、あるスレッドが書き出している途中で
読み込んでも安全なように
*/

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
#include <thread>
#include <mutex>
#include <numeric>

template<class T>
class double_buffer
{
    using value_type        = T;
    using reference         = T&;
    using const_reference   = T const&;
    using pointer           = T*;
private:
    std::vector<T> rdbuf;
    std::vector<T> wtbuf;
    mutable std::mutex mt;//mutableと書いた
public:
    double_buffer() = delete;
    explicit double_buffer(size_t const size) : rdbuf(size), wtbuf(size) {}

    size_t size() const { return rdbuf.size(); }

    void write(T const * const ptr, size_t const size)
    {
        std::unique_lock<std::mutex> lock(mt);
        auto length = std::min(size, wtbuf.size());
        std::copy(ptr, ptr+length, std::begin(wtbuf));
        wtbuf.swap(rdbuf);
    }

    pointer data() const 
    {
        std::unique_lock<std::mutex> lock(mt);
        return rdbuf.data();
    }

    template<class Output>
    void read(Output out) const
    {
        std::unique_lock<std::mutex> lock(mt);
        std::copy(std::cbegin(rdbuf), std::cend(rdbuf), out);
    }

    reference operator[](size_t const i) 
    {
        std::unique_lock<std::mutex> lock(mt);
        return rdbuf[i];
    }
    
    const_reference operator[](size_t const i) const 
    {
        std::unique_lock<std::mutex> lock(mt);
        return rdbuf[i];
    }

    void swap(double_buffer other)
    {
        std::swap(rdbuf, other.rdbuf);
        std::swap(wtbuf, other.wtbuf);
    }


};


//テスト用プリント関数
template<class T>
void print_buffer(double_buffer<T> const& buf)
{
    buf.read(std::ostream_iterator<T>(std::cout, " "));
    std::cout << std::endl;
}

//スレッドを分けてアクセスする例
int main() 
{
    double_buffer<int> buf(10);

    std::thread t([&buf]() {
        for (int i = 1; i < 1000; i+=10)
        {
            int data[10] = {};
            std::iota(std::begin(data), std::end(data), i);
            buf.write(data, std::size(data));

            using namespace std::chrono_literals;
            std::this_thread::sleep_for(100ms);
        }
    });

    auto start = std::chrono::system_clock::now();
    do 
    {
        print_buffer(buf);

        using namespace std::chrono_literals;
        std::this_thread::sleep_for(150ms);
    } while (std::chrono::duration_cast<std::chrono::seconds>(
         std::chrono::system_clock::now() - start).count() < 12);

    t.join();
}

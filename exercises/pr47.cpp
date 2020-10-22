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

template<class T>
class double_buffer
{
    using value_type        = T;
    using reference         = T&;
    using const_reference   = T const&;
    using pointer           = T*;
private:
    std::vector<T> rdbuf;
    std::vector<T> wrbuf;
    mutable std::mutex mt;//mutableと書いた
public:
    double_buffer() = delete;
    explicit double_buffer(size_t const size) : rdbuf(size), wrbuf(size) {}

    size_t size() const { return rdbuf.size(); }

    T& operator[](size_t const i) 
    {
        std::lock_guard<std::mutex> lock(mt);
        return rdbuf[i];
    }

    void write(std::vector<T> const & a)
    {
        wrbuf = a;
        swap(rdbuf, wrbuf);
    }

    void read(std::vector<T> & a)
    {
        std::lock_guard<std::mutex> lock(mt);
        a = rdbuf;
    }
};





int main() 
{
    double_buffer<int> buf(5);
    buf.write(std::vector<int> {1,2,3,4,5});

    std::vector<int> vec;
    buf.read(vec);
    for (auto a : vec) {
        std::cout << a << " ";
    } std::cout << std::endl;
}

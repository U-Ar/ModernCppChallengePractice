#include<iostream>
#include<sstream>
#include<array>
#include<string>
#include<vector>
#include<algorithm>
#include<iterator>

//可変長引数を利用した定義には可変長テンプレートを利用する！

template<typename T, typename First>
T min_value(const First& first) {
    return first;
}

template<typename T, typename First, typename... Rest>
T min_value(const First& first, const Rest&... rest) {
    T m = min_value<T>(rest...);
    if (first <= m) return first;
    return m;
}

//関数ポインタを利用した書き方

template<typename T, typename First>
T min_value2(bool (*comp) (const T &, const T &), const First& first) {
    return first;
}

template<typename T, typename First, typename... Rest>
T min_value2(bool (*comp) (const T &, const T &) , const First& first, const Rest&... rest) {
    T m = min_value2<T>(*comp, rest...);
    if (comp(first,m)) return first;
    return m;
}

template<typename T>
bool comp1(T const & a, T const & b) {
    return a < b;
}

int main() {
    std::cout << min_value<int>(2,1,3,4,5) << std::endl;
    std::cout << min_value<double>(2.1,3.0,4.0,0.28,1) << std::endl;
    std::cout << min_value<int>(1) << std::endl;

    std::cout << min_value2<int>(*(comp1<int>),2,1,3,4,5) << std::endl;
    std::cout << min_value2<double>(*(comp1<double>),2.1,3.0,4.0,0.28,1) << std::endl;
    std::cout << min_value2<int>(*(comp1<int>),1) << std::endl;
}
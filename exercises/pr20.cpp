#include<iostream>
#include<sstream>
#include<array>
#include<string>
#include<vector>
#include<algorithm>
#include<iterator>
#include<list>
#include<cassert>

template<typename C, typename T>
bool contains(const C& container, const T& a) {
    return std::find(container.cbegin(),container.cend(),a)
    != container.end();
}

template<typename C, typename T>
bool contains_any(const C& container, const T& a) {
    return contains(container, a);
}
template<typename C, typename T, typename... T1>
bool contains_any(const C& container, const T& a, const T1... rest) {
    return contains(container, a) || contains_any(container, rest...);
}

template<typename C, typename T>
bool contains_all(const C& container, const T& a) {
    return contains(container, a);
}
template<typename C, typename T, typename... T1>
bool contains_all(const C& container, const T& a, const T1... rest) {
    return contains(container, a) && contains_all(container, rest...);
}

template<typename C, typename T>
bool contains_none(const C& container, const T& a) {
    return !contains(container, a);
}
template<typename C, typename T, typename... T1>
bool contains_none(const C& container, const T& a, const T1... rest) {
    return !contains(container, a) && contains_none(container, rest...);
}

int main() {
    std::vector<int> v{1,2,3,4,5,6};
    assert(contains_any(v,0,3,30));

    std::array<int,6> a{{1,2,3,4,5,6}};
    assert(contains_all(a,1,3,5,6));

    std::list<int> l{1,2,3,4,5,6};
    assert(!contains_none(l,0,6));

    std::list<int> b{1,2,3,4,5,6};
    assert(!contains_none(b,0,8));
}
#include<iostream>
#include<sstream>
#include<array>
#include<string>
#include<vector>
#include<algorithm>
#include<iterator>

template<typename C, typename T>
void push_all(C& container, const T first) {
    container.push_back(first);
}

template<typename C, typename T, typename... T1>
void push_all(C& container, const T first, const T1... rest) {
    container.push_back(first);
    push_all(container, rest...);
}

int main() {
    std::vector<int> a {1};
    std::copy(std::cbegin(a), std::cend(a), 
            std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
    push_all(a, 5, 6, 4, 3, 2);
    std::copy(std::cbegin(a), std::cend(a), 
            std::ostream_iterator<int>(std::cout, " "));
}
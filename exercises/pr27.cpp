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


template <typename Iter>
std::string join(Iter begin, Iter end, std::string delim)
{
    std::ostringstream oss;
    if (begin == end) return std::string("");

    oss << *(begin++);
    for (; begin != end; begin++) {
        oss << delim << *begin ;
    }
    return oss.str();
}

template<typename C>
std::string join(C const & c, std::string delim)
{
    if (c.size() != delim.size() + 1) throw std::invalid_argument("Cannot join");
    
    std::ostringstream oss;
    oss << c[0];
    for (size_t i = 0; i < delim.size(); i++) {
        oss << delim[i] << c[i+1];
    }
    return oss.str();
}


int main() 
{
    std::vector<std::string> a {"a", "b", "c"};
    std::cout << join(a,". ") << std::endl;
    //std::vector<std::string> b;
    //std::cout << join(b,"") << std::endl;
    std::array<std::string, 2> c {"ag", "pz"};
    std::cout << join(c, "a" ) << std::endl;
}

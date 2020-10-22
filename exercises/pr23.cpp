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


template<typename Iter>
std::string bytes_to_hexstr(Iter begin, Iter end, bool const uppercase=false)
{
    std::ostringstream oss;
    if (uppercase) oss.setf(std::ios_base::uppercase);
    for (; begin != end; ++begin)
        oss << std::hex << std::setw(2) << std::setfill('0')
            << static_cast<int>(*begin);
    return oss.str();
}
template<typename C>
std::string bytes_to_hexstr(C const & c, bool const uppercase=false)
{
    return bytes_to_hexstr(std::cbegin(c),std::cend(c),uppercase);
}

int main() {
    std::cout << bytes_to_hexstr(std::vector<int>{1,2,3,4,5}) << std::endl;
    std::cout << bytes_to_hexstr(std::vector<int>{255,100,231,4,5},true) << std::endl;

}

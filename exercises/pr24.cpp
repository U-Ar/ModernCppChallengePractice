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

int help(char a) {
    int b = a - '0';
    if (b >= 0 && b <= 9) return b;
    b = a - 'A' + 10;
    if (b >= 10 && b <= 15) return b;
    b = a - 'a' + 10;
    if (b >= 10 && b <= 15) return b;

    throw std::invalid_argument("Invalid hexadecimal character");
}

std::vector<int> hexstr_to_bytes(std::string s)
{
    std::vector<int> res;
    for (size_t i = 0; i < s.size(); i+=2) {
        res.push_back((help(s[i]) << 4) + help(s[i+1]));
    }
    return res;
}

int main() {
    std::string s = "FF644E7040";
    std::vector<int> a = hexstr_to_bytes(s);
    std::copy(std::begin(a),std::end(a),std::ostream_iterator<int>(std::cout," "));
}

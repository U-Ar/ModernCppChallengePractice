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

std::string capitalize(std::string const & s1) {
    std::istringstream iss(s1);
    std::ostringstream oss;
    std::string tmp;
    while (!iss.eof()) {
        iss >> tmp;
        tmp[0] = std::toupper(tmp[0]);
        oss << tmp << " ";
    }
    return oss.str();
}

int main() {
    std::string s = "the c++ challenger";
    std::cout << capitalize(s) << std::endl;
}

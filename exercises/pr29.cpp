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

bool is_upper_alpha(const char c)
{
    return c-'A' >= 0 && c-'A' <= 25;
}
bool is_digit(const char c) 
{
    return c-'0' >= 0 && c-'0' <= 9;
}

bool validate_number(std::string s)
{
    if (s.size() == 10) {
        for (size_t i = 0; i < 3; i++) {
            if (!is_upper_alpha(s[i])) return false;
        }
        if (s[3] != '-') return false;
        for (size_t i = 4; i < 6; i++) {
            if (!is_upper_alpha(s[i])) return false;
        }
        if (s[6] != ' ') return false;
        for (size_t i = 7; i < 10; i++) {
            if (!is_digit(s[i])) return false;
        }
        return true;
    } else if (s.size() == 11) {
        for (size_t i = 0; i < 3; i++) {
            if (!is_upper_alpha(s[i])) return false;
        }
        if (s[3] != '-') return false;
        for (size_t i = 4; i < 6; i++) {
            if (!is_upper_alpha(s[i])) return false;
        }
        if (s[6] != ' ') return false;
        for (size_t i = 7; i < 11; i++) {
            if (!is_digit(s[i])) return false;
        }
        return true;
    } 
    return false;
}

std::vector<std::string> enumerate_number(std::string & s)
{
    std::vector<std::string> res;
    for (size_t i = 0; i < s.size()-10; i++) {
        std::string a = s.substr(i, 10);
        if (validate_number(a)) res.push_back(a);
    }
    for (size_t i = 0; i < s.size()-11; i++) {
        std::string a = s.substr(i, 11);
        if (validate_number(a)) res.push_back(a);
    }
    return res;
}

int main() 
{
    std::string s = "AJI-VD 293 is a number of AVH-CE 1293 is a";
    std::vector<std::string> a = enumerate_number(s);
    for (int i = 0; i < a.size(); i++) std::cout << a[i] << " ";
}

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
#include<regex> //regexヘッダで正規表現

std::vector<std::string> parse_url(const std::string & s)
{
    std::vector<std::string> result;
    size_t start = 0, i = 0;
    while (s[i] != ':') i++;
    result.push_back(s.substr(0,i));
    
    start = i + 3, i = start;
    while (i < s.size() && s[i] != '/') i++;
    result.push_back(s.substr(start, (i-start+1)));
    if (i == s.size()) return result;
    
    start = i;
    while (i < s.size() && s[i] != '?') i++;
    result.push_back(s.substr(start, (i-start+1)));
    if (i == s.size()) return result;

    start = i;
    while (i < s.size() && s[i] != '#') i++;
    result.push_back(s.substr(start, (i-start+1)));
    if (i == s.size()) return result;

    return result;
}

int main() 
{
    std::vector<std::string> u = parse_url("");
    for (int i = 0; i < u.size(); i++) std::cout << u[i] << " ";
}

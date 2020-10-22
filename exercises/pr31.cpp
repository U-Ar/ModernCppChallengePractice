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
#include<optional> //optional

std::string transform_date(std::string const & text) 
{
    auto rx = std::regex{ R"((\d{1,2})(\.|-|\/)(\d{1,2})(\.|-|\/)(\d{4}))" };
    return std::regex_replace(text.c_str(), rx, "$5-$3-$1");
}

int main() 
{
    using namespace std::string_literals;
    std::cout << transform_date("today is 1/12/2017!"s);
}

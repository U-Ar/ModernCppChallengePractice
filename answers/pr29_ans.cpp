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


bool validate_license_plate_format(std::string const & str)
{
    std::regex rx(R"([A-Z]{3}-[A-Z]{2} \d{3,4})");
    return std::regex_match(str.c_str(), rx);
}

//すべてのマッチを反復処理するために、"()*"でパターンを繰り返しつつsregex_iteratorを使う
std::vector<std::string> extract_license_plate_numbers(std::string const & str)
{
    std::regex rx(R"(([A-Z]{3}-[A-Z]{2} \d{3,4})*)");
    std::smatch match;
    std::vector<std::string> results;

    for (auto i = std::sregex_iterator(std::cbegin(str),std::cend(str),rx);
    i != std::sregex_iterator(); ++i) {
        if ((*i)[1].matched) results.push_back(i->str());
    }
    return results;

}

int main() 
{
    std::string s = "AJI-VD 293 is a number of AVH-CE 1293 is a";
    std::vector<std::string> a = extract_license_plate_numbers(s);
    for (int i = 0; i < a.size(); i++) std::cout << a[i] << " ";
}

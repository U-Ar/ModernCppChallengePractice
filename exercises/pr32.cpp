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
#include<optional> //optional(C++17)
#include<ios>
#include<iomanip>

/*
int main() 
{
    std::vector<int> pascal(1,1);
    for (size_t i = 0; i < 10; i++) {
        for (int j = 0; j < 9 - i; j++) std::cout << "   ";
        for (size_t j = 0; j < pascal.size(); j++) {
            std::cout << std::right << std::setfill(' ') << std::setw(3)
            << pascal[j] << "   ";
        }
        std::cout << std::endl;
        for (size_t j = pascal.size(); j >= 1; j--) {
            pascal[j] = pascal[j-1] + pascal[j];
        }
        pascal[0] = 1; pascal.push_back(1);
    }
}*/

int main() 
{
    std::cout << "How many lines of Pascal's triangle do you need?: " << std::endl;
    int a;
    std::cin >> a;
    std::cout << "length of padding: " << std::endl;
    int b;
    std::cin >> b;

    std::vector<int> pascal(1,1);
    for (size_t i = 0; i < a; i++) {
        for (int j = 0; j < (a - 1 - i)*b; j++) std::cout << " ";
        for (size_t j = 0; j < pascal.size(); j++) {
            std::cout << std::right << std::setfill(' ') << std::setw(b)
            << pascal[j];
            for (int k = 0; k < b; k++) std::cout << " ";
        }
        std::cout << std::endl;
        for (size_t j = pascal.size(); j >= 1; j--) {
            pascal[j] = pascal[j-1] + pascal[j];
        }
        pascal[0] = 1; pascal.push_back(1);
    }
}

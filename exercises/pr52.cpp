#include<algorithm>
#include<array>
#include<cassert>
#include<chrono>
#include<cmath>
#include<cstdlib>
#include<ctime>
#include<fstream>
#include<functional>
#include<iomanip>
#include<ios>
#include<iostream>
#include<iterator>
#include<locale>
#include<map>
#include<mutex>
#include<numeric>
#include<sstream>
#include<string>
#include<thread>
#include<utility>
#include<vector>

void string_permutations(std::string const& str)
{
    std::string tmp(str);
    do 
    {
        std::cout << tmp << std::endl;
    } while (std::next_permutation(tmp.begin(),tmp.end()));
}

int main() 
{
    std::cout << "input string: " << std::endl;
    std::string s; 
    std::cin >> s;
    string_permutations(s);
}

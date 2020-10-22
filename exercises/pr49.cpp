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

bool isalpha(char const c)
{
    return (c >= 'a' && c <= 'z') | (c >= 'A' && c <= 'Z'); 
}

int ctoi(char const c)
{
    if (c >= 'a' && c <= 'z') return c;
    if (c >= 'A' && c <= 'Z') return 'a' + c - 'A';
    else throw std::invalid_argument("Not alphabet.");
}

void histogram(std::string const& str, std::string const& filename)
{
    std::map<char, int> mp;
    double sum = 0;

    for (char c = 'a'; c <= 'z'; c++)
    {
        mp[c] = 0;
    }

    for (size_t i = 0; i < str.size(); i++) { 
        if (isalpha(str[i])) {
            mp[ctoi(str[i])]++; sum += 1;
        }
    }
    
    std::ofstream ofs("tmp.data",std::ios::trunc);
    for (auto a : mp)
    {
        ofs << a.first << " " << static_cast<double>(a.second)/sum << std::endl;
    }
    ofs.close();

    std::cout << "unset grid" << std::endl;
    std::cout << "set style data histogram" << std::endl;
    std::cout << "set style fill solid" << std::endl;
    std::cout << "set terminal png" << std::endl;
    std::cout << "set output \"" << filename << "\"" << std::endl;
    std::cout << "set xlabel \'alphabet\'" << std::endl;
    std::cout << "set ylabel \'frequency\'" << std::endl;
    std::cout << "set yrange [0:]" << std::endl;
    std::cout << "plot \'tmp.data\' using 2:xtic(1) title \"frequency\" linecolor rgb \'light-red\'" << std::endl;
    std::cout << "unset terminal" << std::endl;
}


int main(int argc, char *argv[]) 
{
    //1: file name
    std::string filename(argv[1]);
    //2: object string
    std::vector<std::string> args(argv+2, argv+argc);
    std::string s;
    for (auto a : args) s += a;
    histogram(s,filename);
}
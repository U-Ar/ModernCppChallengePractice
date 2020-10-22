#include<cassert>
#include<chrono>
#include<cmath>
#include<cstdlib>
#include<ctime>
#include<cctype>
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
#include<optional>
#include<random>
#include<set>
#include<sstream>
#include<string>
#include<thread>
#include<type_traits>
#include<utility>
#include<vector>

class Code
{
    int offset;
public:
    Code() : Code(1) {}
    explicit Code(int const o) : offset(o) {}
    
    std::string encode(std::string const& s)
    {
        std::string res = s;
        for (auto& c : res)
        {
            c = (c-'A'+offset+26)%26 + 'A';
        }
        return res;
    }

    std::string decode(std::string const& s)
    {
        std::string res = s;
        for (auto& c : res)
        {
            c = (c-'A'-offset+26)%26 + c;
        }
        return res;
    }
};

int main() {
    Code coder(5);
    std::cout << coder.encode("IAMNUMBERONE") << std::endl;
}
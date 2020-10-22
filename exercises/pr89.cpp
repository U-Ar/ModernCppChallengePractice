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
    std::string const key;
public:
    Code() : Code("A") {}
    explicit Code(std::string const& s) : key(s) {}
    
    std::string encode(std::string const& s)
    {
        std::string res = s;
        size_t i = 0;
        for (auto& c : res)
        {
            c = ((c-'A')+(key[(i++)%key.size()]-'A')+26)%26 + 'A';
        }
        return res;
    }

    std::string decode(std::string const& s)
    {
        std::string res = s;
        size_t i = 0;
        for (auto& c : res)
        {
            c = ((c-'A')-(key[(i++)%key.size()]-'A')+26)%26 + 'A';
        }
        return res;
    }
};

int main() {
    Code coder("FFFFF");
    std::cout << coder.encode("IAMNUMBERONE") << std::endl;

    std::cout << coder.decode(coder.encode("IAMNUMBERONE")) << std::endl;
}
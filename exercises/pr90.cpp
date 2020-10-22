#include<bitset>
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

class Base64
{
    std::map<std::string,char> encode_table; 
    std::map<char,std::string> decode_table;
public:
    Base64() : encode_table{}, decode_table{}
    {
        for (int i = 0; i < 26; i++) {
            std::stringstream ss;
            ss << std::setw(6) << std::setfill('0') << std::right 
               << std::bitset<6>(i);
            encode_table[ss.str()] = i+'A';
            decode_table[i+'A'] = ss.str();
        }
        for (int i = 26; i < 52; i++) {
            std::stringstream ss;
            ss << std::setw(6) << std::setfill('0') << std::right 
               << std::bitset<6>(i);
            encode_table[ss.str()] = (i-26)+'a';
            decode_table[(i-26)+'a'] = ss.str();
        }
        for (int i = 52; i < 62; i++) {
            std::stringstream ss;
            ss << std::setw(6) << std::setfill('0') << std::right 
               << std::bitset<6>(i);
            encode_table[ss.str()] = (i-52)+'0';
            decode_table[(i-52)+'0'] = ss.str();
        }
        encode_table["111110"] = '+';
        decode_table['+'] = "111110";
        encode_table["111111"] = '/';
        decode_table['/'] = "111111";
    }    

    std::string encode(std::string const& s)
    {
        std::string plain = s;
        std::string res;
        for (int i = 0; i < (6-s.size()%6)%6; ++i) plain += '0';
        for (size_t i = 0; i < plain.size(); i+=6)
        {
            res += encode_table[plain.substr(i,6)];
        }
        for (int i = 0; i < (4-res.size()%4)%4; ++i) res += '=';
        return res;
    }


    std::string decode(std::string const& s)
    {
        std::string res;
        for (size_t i = 0; i < s.size(); ++i)
        {
            if (decode_table.find(res[i]) != decode_table.end())
            res += decode_table[res[i]];
        }
        return res;
    }

};


int main() {
    Base64 code;
    std::cout << code.encode("10111010111010101011101011001000000101111101011110101") << std::endl;
    std::cout << code.decode(code.encode("10111010111010101011101011001000000101111101011110101")) << std::endl;

}
#include<bitset>
#include<cassert>
#include<chrono>
#include<cmath>
#include<cstddef>
#include<cstdlib>
#include<ctime>
#include<cctype>
#include<filesystem>
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
#include<regex>
#include<set>
#include<sstream>
#include<string>
#include<string_view>
#include<thread>
#include<type_traits>
#include<utility>
#include<vector>

#include<pngwriter.h>


struct ean13
{
    explicit ean13(std::string const& code)
    {
        if (code.size() == 13)
        {
            if (code[12] != '0' + get_crc(code.substr(0,12)))
                throw std::runtime_error("Not and EAN-13 format.");
            number = code;
        }
        else if (code.size() == 12)
        {
            number = code + std::string(1,'0'+get_crc(code));
        }
    }

    explicit ean13(unsigned long long code) : ean13(std::to_string(code)) {}

    std::array<unsigned char, 13> to_array() const
    {
        std::array<unsigned char, 13> result;
        for (int i = 0; i < 13; ++i)
            result[i] = static_cast<unsigned char>(number[i]-'0');
        return result;
    }

    std::string to_string() const noexcept {return number;}

private:
    unsigned char get_crc(std::string const& code)
    {
        unsigned char const weights[12] = {1,3,1,3,1,3,1,3,1,3,1,3};
        size_t index = 0;
        auto const sum = std::accumulate(
            std::cbegin(code),std::cend(code),0,
            [&weights,&index](int const total,char const c)
            {
                return total + weights[index++] * (c - '0');
            }
        );
        return static_cast<unsigned char>(10 - sum%10);
    }
    std::string number;
};


struct ean13_barcode_generator
{
    void create(ean13 const& code,
                std::string const& filename,
                int const digit_width = 3,
                int const height = 50,
                int const margin = 10) const;
private:
    int draw_digit(unsigned char const code, unsigned int const size,
                   pngwriter& image,
                   int const x, int const y,
                   int const digit_width, int const height) const 
    {
        std::bitset<7> const bits(code);
        int pos = x;
        for (int i = size-1; i >= 0; --i)
        {
            if (bits[i] != 0)
            {
                image.filledsquare(pos,y,pos+digit_width,y+height,0,0,0);
            }
            pos += digit_width;
        }
        return pos;
    }
};


int main()
{
    
}
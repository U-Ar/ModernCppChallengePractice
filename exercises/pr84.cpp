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


class barcode_generator
{
public:
    barcode_generator() : barcode_generator(5) {}
    explicit barcode_generator(int m) :
        module{m}, character{m*7}, width{113*m}, height{30*m},
        odd_left{
            0b1101,0b11001,0b10011,0b111101,0b100011,
            0b110001,0b101111,0b111011,0b110111,0b1011
        },
        even_left{
            0b100111,0b110011,0b11011,0b100001,0b11101,
            0b111001,0b101,0b10001,0b1001,0b10111
        },
        even_right{
            0b1110010,0b1100110,0b1101100,0b1000010,0b1011100,
            0b1001110,0b1010000,0b1000100,0b1001000,0b1110100
        },
        leading{
            0b000000,0b001011,0b001101,0b001110,0b010011,
            0b011001,0b011100,0b010101,0b010110,0b011010
        }
    {}

    void line(pngwriter& png, int const i, int const w)
    {
        png.filledsquare(i*module+1,0,(i+w)*module,height,0,0,0);
    }

    void generate_character(pngwriter& png, int const i, int const c, int const ld)
    {
        int pos, mask;
        if (i <= 5)
        {
            pos = 14 + i * 7;
            if ((ld >> (5-i)) & 0b1) mask = even_left[c];
            else mask = odd_left[c];
        }
        else 
        {
            pos = 61 + (i-6) * 7;
            mask = even_right[c];
        }
        pos += 6;
        while (mask > 0)
        {
            if (mask & 0b0000001 == 1)
            {
                line(png,pos,1);
            }
            mask = (mask >> 1);
            --pos;
        }
    }

    void generate(std::string const& code, std::string const& filename)
    {
        if (code.size() != 13) throw std::runtime_error("invalid EAN-13 code");
        pngwriter png(width,height,0,filename.c_str());
        png.filledsquare(0,0,width,height,1.0,1.0,1.0);
        //left/right guard
        png.filledsquare(11*module+1,0,12*module,height,0,0,0);
        png.filledsquare(13*module+1,0,14*module,height,0,0,0);
        png.filledsquare(103*module+1,0,104*module,height,0,0,0);
        png.filledsquare(105*module+1,0,106*module,height,0,0,0);
        //center guard
        png.filledsquare(57*module+1,0,58*module,height,0,0,0);
        png.filledsquare(59*module+1,0,60*module,height,0,0,0);

        std::string nums = code.substr(1,12);
        
        for (size_t i = 0; i < nums.size(); i++)
        {
            generate_character(png,i,(nums[i]-'0'),leading[code[0]-'0']);
        }

        png.close();
    }

private:
    int module, character, width, height;
    std::vector<int> odd_left, even_left, even_right, leading;
};


int main()
{
    barcode_generator gen{5};
    gen.generate("5901234123457","bar.png");
}
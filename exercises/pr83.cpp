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

int main()
{
    int const width = 700;
    int const height = 150;
    
    char fontpath[] = "/mnt/c/Windows/fonts/arial.ttf";

    std::random_device rd;
    auto seed_data = std::array<int, std::mt19937::state_size> {};
    std::generate(std::begin(seed_data),std::end(seed_data),std::ref(rd));
    std::seed_seq seq(std::cbegin(seed_data), std::cend(seed_data));
    auto eng = std::mt19937{ seq };
    
    auto uda = std::uniform_real_distribution<>{-M_PI/4,M_PI/4};
    std::uniform_int_distribution<> udx(0,width);
    std::uniform_int_distribution<> udy(0,height);
    std::uniform_int_distribution<> udc(0,65535);
    std::uniform_int_distribution<> udt(0,25);


    pngwriter png(width,height,0,"captcha.png");
    for (int i = 0; i <= width; i++)
    {
        png.line(i,0,i,150,(0.7+i/700.0*0.3),
            (0.7+i/700.0*0.3),
            (0.7+i/700.0*0.3));
    }
    
    for (int i = 0; i < 6; i++)
    {
        auto tmp = std::string(1,char('A'+udt(eng)));
        std::vector<char> text(tmp.begin(),tmp.end());
        text.push_back('\0');
        png.plot_text(
            fontpath,
            50,
            100*i+50,
            height/2,
            uda(eng),
            &text[0],
            0,0,0
        );
    }
    for (int i = 0; i < 4; i++)
    {
        png.line(udx(eng),0,udx(eng),height,udc(eng),udc(eng),udc(eng));
        png.line(0,udy(eng),width,udy(eng),udc(eng),udc(eng),udc(eng));
    }
    png.close();
    
}
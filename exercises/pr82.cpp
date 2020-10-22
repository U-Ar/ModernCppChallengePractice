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

    pngwriter png(450,300,0,"test.png");

    png.filledsquare(0,0,150,300,0,0,65535);
    png.filledsquare(151,0,300,300,65535,65535,0);
    png.filledsquare(301,0,450,300,65535,0,0);

        
    png.close();

    return 0;
}
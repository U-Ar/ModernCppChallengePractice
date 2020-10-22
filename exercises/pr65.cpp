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
#include<random>
#include<sstream>
#include<string>
#include<thread>
#include<type_traits>
#include<utility>
#include<vector>


class Logger 
{
private:    
    std::mutex mx;
public:
    Logger() : {}

    void log(string cosnt& s)
    {
        std::lock_guard<std::mutex> lock(mx);
        std::cout << s << std::endl;
    }
};

int main()
{
    
}
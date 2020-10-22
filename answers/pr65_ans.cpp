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
protected:
    Logger() = default;
public:
    static Logger& instance()
    {
        static Logger lg;
        return lg;
    }

    //コピーも代入も禁止
    Logger(Logger const&) = delete;
    Logger& operator=(Logger const&) = delete;

    void log(std::string const& s)
    {
        std::lock_guard<std::mutex> lock(mx);
        std::cout << s << std::endl;
    }
};

int main()
{
    std::vector<std::thread> modules;

    for (int id = 1; id <= 5; id++)
    {
        modules.emplace_back([id]() {
            std::random_device rd;
            std::mt19937 mt(rd());
            std::uniform_int_distribution<> ud(100,1000);
            Logger::instance().log("module " + std::to_string(id) + " started");

            std::this_thread::sleep_for(std::chrono::milliseconds(ud(mt)));

            Logger::instance().log("module " + std::to_string(id) + " finished");
        });
    }

    for (auto & m : modules) m.join();
}
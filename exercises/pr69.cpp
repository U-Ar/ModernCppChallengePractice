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
#include<random>
#include<set>
#include<sstream>
#include<string>
#include<thread>
#include<type_traits>
#include<utility>
#include<vector>


class Social_number_generator
{
    std::random_device rd;
    std::mt19937 eng;
    int const man;
    int const woman;
    int const random_len;
    int const sumfactor;
    int year, month, day;
    std::set<int> idset;
public:
    explicit Social_number_generator(
        int const m, int const w,
        int const r,
        int const s)
    : man(m), woman(w), random_len(r), sumfactor(s)
    {
        auto seed_data = std::array<int, std::mt19937::state_size> {};
        std::generate(seed_data.begin(),seed_data.end(),std::ref(rd));
        std::seed_seq seq(seed_data.cbegin(),seed_data.cend());
        eng.seed(seq);
        int tmp = 1;
        for (int i = 0; i < random_len; i++) tmp *= 10;
    }

    std::string generate(bool const sex, int const y, 
        int const m, int const d)
    {
        std::ostringstream oss;
        oss << (sex ? man : woman)
            << std::setw(4) << std::setfill('0') << std::right << y 
            << std::setw(2) << std::setfill('0') << std::right << m
            << std::setw(2) << std::setfill('0') << std::right << d;
        int tmp = 1;
        for (int i = 0; i < random_len; i++) tmp *= 10;
        std::uniform_int_distribution<> dist(0,tmp-1);
        int r = dist(eng);

        time_t now = time(0);
        struct tm tstruct;
        tstruct = *localtime(&now);

        if (tstruct.tm_year == year 
            && tstruct.tm_mon == month 
            && tstruct.tm_mday == day)
        {
            while (idset.find(r) != idset.end()) r = dist(eng);

            idset.insert(r);
            oss << std::setw(random_len) << std::setfill('0')
                << std::right << r;
        } 
        else 
        {
            year = tstruct.tm_year;
            month = tstruct.tm_mon;
            day = tstruct.tm_mday;
            oss << std::setw(random_len) << std::setfill('0')
                << std::right << r;
        }
        std::string result(oss.str());
        oss << checksum(result);
        return oss.str();
    }

    int checksum(std::string const& num)
    {
        int sum = 0;
        for (int i = 0; i < num.size(); i++)
        {
            sum += (num[i]-'0')*num.size();
        }
        for (int c = 0; c < 10; c++)
        {
            if ((sum + c) % sumfactor == 0) return c;
        }
        throw std::runtime_error("checksum error");
    }
};


int main() 
{
    Social_number_generator northeria(7,9,5,11);
    Social_number_generator southeria(2,1,4,10);

    std::cout << northeria.generate(0,1998,8,21) << std::endl;
    std::cout << southeria.generate(0,1998,8,21) << std::endl;


}
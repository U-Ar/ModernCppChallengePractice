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

char itoc(int const a)
{
    if (a <= 25) return a + 'A';
    return ' ';
}

template <typename E = std::mt19937,
          typename D = std::uniform_int_distribution<> >
bool evolve(std::string& s, std::string const& ans, std::vector<bool>& finished, E& engine, D& dist)
{
    bool result = true;
    for (size_t i = 0; i < s.size(); i++)
    {
        if (!finished[i]) 
        {
            s[i] = itoc(dist(engine));
            if (s[i] == ans[i]) finished[i] = true; 
            if (!finished[i]) result = false; 
        }
    }
    return result;
}
         

void weasel_program(std::string const& ans)
{
    std::string s(ans);
    std::vector<bool> finished(s.size(),false);
    std::random_device rd;
    auto seed_data = std::array<int, std::mt19937::state_size> {};
    std::generate(seed_data.begin(),seed_data.end(),std::ref(rd));
    std::seed_seq seq(seed_data.cbegin(),seed_data.cend());
    auto eng = std::mt19937{ seq };
    auto dist = std::uniform_int_distribution<> {0, 26};
    bool f = false;
    std::for_each(s.begin(),s.end(),[&eng,&dist](char& c) { c = itoc(dist(eng)); } );
    for (int i = 0; !f; i++)
    {
        f = evolve(s,ans,finished,eng,dist);
        std::cout << std::setfill(' ') << std::setw(6) << std::left 
        << i << s << std::endl;
    }
}

int main() 
{
    weasel_program("METHINKS IT IS LIKEAWEASEL");
}
#include<array>
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
#include<sstream>
#include<string>
#include<thread>
#include<type_traits>
#include<utility>
#include<vector>

template<typename F>
bool check_password(std::string const& pass, size_t const l, F&& f)
{
    return pass.size() >= l && std::forward<F>(f)(pass);
}

template<typename F1, typename... F>
bool check_password(std::string const& pass, size_t const l, F1&& f1, F&&... f)
{
    return std::forward<F1>(f1)(pass) && check_password(pass,l,f...);
}


bool complex(std::string const& s)
{
    return (std::find_if(s.begin(),s.end(),isupper) != s.end()) &&
           (std::find_if(s.begin(),s.end(),islower) != s.end()) &&
           (std::find_if(s.begin(),s.end(),isdigit) != s.end()) &&
           (std::find_if(s.begin(),s.end(),ispunct) != s.end());
}

int main()
{
    std::string s1 {"P1a+"};
    assert(check_password(s1,3,complex));
    //assert(check_password(s1,5,complex));
    std::string s2 {"p1a+"};
    assert(check_password(s2,5,complex));

}
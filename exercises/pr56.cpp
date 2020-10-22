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
#include<sstream>
#include<string>
#include<thread>
#include<utility>
#include<vector>

template <typename Iterator,typename Output, typename Func>
void select(Iterator const begin, Iterator const end, Output result, Func func)
{
    std::transform(begin,end,result,func);
}

template <typename T, typename Func>
auto select(std::vector<T> const& vec, Func func)
{
    std::vector<std::declval<func>()(typename T)() > result;
    select(std::cbegin(vec),std::cend(vec),
    std::back_inserter(result),func);
    return result;
}

struct book
{
    int id;
    std::string title;
    std::string author;
}

int main() 
{
    std::cout << "This program is incomplete.\n";
    return 0;
    
    std::vector<book> books {
        {101,"A","B"},
        {222,"C","D"},
        {333,"E","F"}
    };
    auto titles = select(books,[](book const & b){ return b.title; });
    for (auto a : titles)
    {
        std::cout << a << std::endl;
    }
}

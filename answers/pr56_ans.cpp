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


template <
typename T, typename A, typename F,
typename R = typename std::decay<typename std::result_of<
             typename std::decay<F>::type&(
             typename std::vector<T,A>::const_reference)>::type>::type>
std::vector<R> select(std::vector<T,A> const& c, F&& f)
{
    std::vector<R> v;
    std::transform(c.begin(),c.end(),std::back_inserter(v),
                   std::forward<F>(f));
    return v;
}

struct book
{
    int id;
    std::string title;
    std::string author;
};

int main() 
{
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

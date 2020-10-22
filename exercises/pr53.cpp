#include<algorithm>
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


struct movie
{
    std::string name;
    int rank;
    movie(std::string const & s, int r) : name(s), rank(r) {}
};

double average_ranks(std::vector<movie> & list)
{
    double result = 0.0;
    size_t out = list.size() / 20;
    std::sort(list.begin(),list.end(),[](movie const& a, movie const& b)
    { return a.rank <= b.rank;});
    int sum = std::accumulate(list.begin()+out, list.end()-out,0,
    [](int acc, movie m) { return acc + m.rank; });
    return static_cast<double>(sum)/static_cast<double>(list.size()-2*out);
}

int main() 
{
    std::vector<movie> 
    vec { {"a", 3}, {"b", 10}, {"d", 5}} ;
    std::cout << std::fixed << std::setprecision(1) << average_ranks(vec) << std::endl;
}

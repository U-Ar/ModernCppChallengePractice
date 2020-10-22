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
#include<set>
#include<sstream>
#include<string>
#include<string_view>
#include<thread>
#include<type_traits>
#include<utility>
#include<vector>

#define ASIO_STANDALONE 
#define ASIO_HAS_STD_ADDRESSOF 
#define ASIO_HAS_STD_ARRAY 
#define ASIO_HAS_CSTDINT 
#define ASIO_HAS_STD_SHARED_PTR 
#define ASIO_HAS_STD_TYPE_TRAITS 

#include "asio/include/asio.hpp"



int main()
{
    asio::io_service io_service;

    asio::ip::tcp::resolver resolver(io_service);
    asio::ip::tcp::resolver::query query(asio::ip::host_name(),"");
    asio::ip::tcp::resolver::iterator iter = resolver.resolve(query);
    asio::ip::tcp::resolver::iterator end;
    while (iter != end)
    {
        asio::ip::tcp::endpoint ep = *iter++;
        std::cout << ep << std::endl; 
    }
}
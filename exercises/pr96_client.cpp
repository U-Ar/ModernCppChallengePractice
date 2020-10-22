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


void run_client(std::string const& host, short const port)
{
    try
    {
        asio::io_context context;
        asio::ip::tcp::socket tcp_socket(context);
        asio::ip::tcp::resolver resolver(context);
        asio::connect(tcp_socket, 
                      resolver.resolve({ host.c_str(), std::to_string(port) }));
        while (true)
        {
            std::cout << "number [1-99]: " ;
            int number;
            std::cin >> number;
            if (std::cin.fail() || number < 1 || number > 99)
                break;
            
            auto request = std::to_string(number);
            tcp_socket.write_some(asio::buffer(request,request.size()));

            std::array<char,1024> reply;
            auto reply_length = tcp_socket.read_some(
                asio::buffer(reply,reply.size())
            );

            std::cout << "reply is: ";
            std::cout.write(reply.data(), reply_length);
            std::cout << std::endl;
        }
    }
    catch (std::exception const& e)
    {
        std::cerr << "exception: " << e.what() << std::endl;
    }
}

int main()
{
    run_client("localhost", 11234);
}
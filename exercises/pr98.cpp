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


#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>

using namespace cURLpp::Options;



std::stringstream get_folders()
{
    std::stringstream str;
    try
    {
        cURLpp::Easy req;
        req.setOpt(new Url("imaps://imap.mail.me.com:993"));
        req.setOpt(new WriteFunction(
            cURLpp::Types::WriteFunctionFunctor(
                [&str](char* pstr, size_t size, size_t nmemb) {
                    size_t realsize = size*nmemb;
                    str << std::string{pstr};
                    return realsize;
                })
        ));
        req.setOpt(new UserAgent("yuma.arakawa@icloud.com"));
        req.setOpt(new UserPwd("qweR Tyui821"));
        req.perform();
    }
    catch (cURLpp::LogicError const& error)
    {
        std::cerr << error.what() << std::endl;
    }
    catch (cURLpp::RuntimeError const& error)
    {
        std::cerr << error.what() << std::endl;
    }
    return str;
}


int main()
{
    std::string res = get_folders().str();
    std::cout << res << std::endl;   
}
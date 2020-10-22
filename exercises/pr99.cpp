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


#include "json.hpp"
using json = nlohmann::json;


std::stringstream get_translated(std::string text,
                           std::string source,
                           std::string target)
{
    std::stringstream str;
    std::string const web_api = "https://script.google.com/macros/s/AKfycbzIzkyApKP3ZFLwwD2fZqOKs2aAdlST2IiQxOMjKjFu0_HJ2Xw/exec";
    try
    {
        cURLpp::Easy req;
        req.setOpt(new Url(web_api+std::string("?text=")+text
                                  +std::string("&source=")+source
                                  +std::string("&target=")+target));
        req.setOpt(new WriteFunction(
            cURLpp::Types::WriteFunctionFunctor(
                [&str](char* pstr, size_t size, size_t nmemb) {
                    size_t realsize = size*nmemb;
                    str << std::string{pstr};
                    return realsize;
                })
        ));
        req.setOpt(new FollowLocation(1L));
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
    std::cout << "target text: ";
    std::string text;
    std::cin >> text;
    std::cout << "source language: ";
    std::string source;
    std::cin >> source;
    std::cout << "target language: ";
    std::string target;
    std::cin >> target;
    auto res = get_translated(text,source,target);
    std::cout << res.str() << std::endl;
    json j;
    j = json::parse(res.str());

    if (j.at("code") == 200)
    {
        std::cout << j.at("text") << std::endl;
    } else {
        std::cout << "Invalid query.\n";
    }
}
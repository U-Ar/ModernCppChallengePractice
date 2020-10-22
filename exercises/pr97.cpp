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
std::stringstream get_json_document(std::string const& url)
{
    std::stringstream str;
    try
    {
        cURLpp::Easy req;
        req.setOpt(new Url(url));
        req.setOpt(new WriteFunction(
            cURLpp::Types::WriteFunctionFunctor(
                [&str](char* pstr, size_t size, size_t nmemb) {
                    size_t realsize = size*nmemb;
                    str << std::string{pstr};
                    return realsize;
                })
        ));
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

struct exchange_info
{
    double delay_15m_price;
    double latest_price;
    double buying_price;
    double selling_price;
    std::string symbol;
};

using blockchain_rates = std::map<std::string, exchange_info>;

void from_json(json const& jdata, exchange_info& info)
{
    info.delay_15m_price = jdata.at("15m").get<double>();
    info.latest_price = jdata.at("last").get<double>();
    info.buying_price = jdata.at("buy").get<double>();
    info.selling_price = jdata.at("sell").get<double>();
    info.symbol = jdata.at("symbol").get<std::string>();
}



int main()
{
    std::stringstream data = get_json_document("https://blockchain.info/ticker");
    json jdata;
    data >> jdata;
    blockchain_rates rates = jdata;
    for (auto const& [title, info] : rates)
    {
        std::cout << "1BPI = " << info.latest_price
        << " " << title << std::endl;
    }

}
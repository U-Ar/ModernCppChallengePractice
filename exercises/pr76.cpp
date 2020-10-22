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
#include<optional>
#include<random>
#include<set>
#include<sstream>
#include<string>
#include<thread>
#include<type_traits>
#include<utility>
#include<vector>

#include "json.hpp"



struct movie
{
    int id;
    std::string title;
    int year;
    int length;
    std::vector<std::string> directors;
    std::vector<std::string> writers;
    std::vector<std::pair<std::string, std::string>> casts;
};



using casts_type = typename std::vector<std::pair<std::pair<std::string,std::string>,std::pair<std::string,std::string>>>;
casts_type casts(std::vector<std::pair<std::string,std::string>>const & vec)
{
    casts_type res;
    for (auto v : vec)
    {
        res.push_back(std::make_pair(std::make_pair("role",v.first),std::make_pair("name",v.second)));
    }
    return res;
}

void seriarize_json(std::string const& filename, std::vector<movie> const& movies)
{
    using json = nlohmann::json;

    json result; 
    std::vector<json> v;
    
    for (auto const& m : movies)
    {
        json j;
        j["id"] = m.id;
        j["title"] = m.title;
        j["year"] = m.year;
        j["length"] = m.length;

        j["cast"] = casts(m.casts);
        j["directors"] = m.directors;
        j["writers"] = m.writers;    
        
        v.push_back(j);
    }

    result["movies"] = v;


    std::ofstream ofs(filename);
    ofs << std::setw(4) << result << std::endl;
}


std::vector<movie> deseriarize_json(std::string const& filename)
{
    using json = nlohmann::json;
    std::ifstream ifs(filename);
    json j;
    ifs >> j;

    std::vector<movie> result;

    for (auto const& element : j.at("movies"))
    {
        movie m;

        m.id = element.at("id").get<int>();
        m.title = element.at("title").get<std::string>();
        m.year = element.at("year").get<int>();
        m.length = element.at("length").get<int>();
        for (auto const& role : element.at("cast"))
        {
            m.casts.push_back(std::make_pair(
                role.at("role").get<std::string>(),
                role.at("name").get<std::string>()
            ));
        }
        for (auto const& d : element.at("directors"))
        {
            m.directors.push_back(d);
        }
        for (auto const& w : element.at("writers"))
        {
            m.writers.push_back(w);
        }
        result.push_back(m);
    }

    return result;
}


int main()
{
    std::vector<movie> res = 
    deseriarize_json("pr75.json");

    seriarize_json("pr75_out.json",res);

}
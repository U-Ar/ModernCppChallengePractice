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

#include "tinyxml2.h"
#include "json.hpp"

using namespace tinyxml2;


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


std::vector<movie> xml_to_movies(const char* filename)
{
    std::vector<movie> result;

    XMLDocument doc;
    doc.LoadFile(filename);

    auto root_element = doc.RootElement();
    if (!root_element){
        std::cout << "xml:rootelement Error" << std::endl;
        return {};
    }

    XMLElement* child_element = root_element->FirstChildElement("movie");

    while (child_element)
    {
        movie m;
        m.id = std::stoi(child_element->Attribute("id"));
        m.title = child_element->Attribute("title");
        m.year = std::stoi(child_element->Attribute("year"));
        m.length = std::stoi(child_element->Attribute("length"));

        XMLElement* cast_element = child_element->FirstChildElement("cast"); 
        cast_element = cast_element->FirstChildElement("role"); 
        while (cast_element)
        {
            m.casts.push_back(std::make_pair(
                cast_element->Attribute("star"),
                cast_element->Attribute("name")
            ));
            cast_element = cast_element->NextSiblingElement("role");
        }

        XMLElement* directors_element = child_element->FirstChildElement("directors");
        XMLElement* director_element = directors_element->FirstChildElement("director");
        while (director_element)
        {
            m.directors.push_back(director_element->Attribute("name"));
            director_element = director_element->NextSiblingElement("director");
        }

        XMLElement* writers_element = child_element->FirstChildElement("writers");
        XMLElement* writer_element = writers_element->FirstChildElement("writer");
        while (writer_element)
        {
            m.writers.push_back(writer_element->Attribute("name"));
            writer_element = writer_element->NextSiblingElement("writer");
        }

        result.push_back(m);

        child_element = child_element->NextSiblingElement("movie");
    }

    return result;
}

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

void deseriarize_json(std::string const& filename, std::vector<movie> const& movies)
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


int main()
{
    std::vector<movie> res = xml_to_movies("pr73.xml");

    deseriarize_json("pr75.json",res);
}
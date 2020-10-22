/*
XPathの利用
tinyxml2がサポートしていなかったためスルー
*/
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

void movies_to_xml(const char* filename, std::vector<movie> const& movies)
{
    XMLDocument doc;
    doc.Parse(R"(<?xml version="1.0"?><movies></movies>)");
    
    auto movies_element = doc.FirstChildElement();
    
    for (movie const& m : movies)
    {
        auto movie_element = movies_element->InsertNewChildElement("movie");
        movie_element->SetAttribute("id",m.id);
        movie_element->SetAttribute("title",m.title.c_str());
        movie_element->SetAttribute("year",m.year);
        movie_element->SetAttribute("length",m.length);

        auto cast_element = movie_element->InsertNewChildElement("cast");
        for (auto c : m.casts)
        {
            auto role_element = cast_element->InsertNewChildElement("role");
            role_element->SetAttribute("role",c.first.c_str());
            role_element->SetAttribute("name",c.second.c_str());
        }
        auto directors_element = movie_element->InsertNewChildElement("directors");
        for (auto d : m.directors)
        {
            auto director_element = directors_element->InsertNewChildElement("director");
            director_element->SetAttribute("name",d.c_str());
        }
        auto writers_element = movie_element->InsertNewChildElement("writers");
        for (auto d : m.writers)
        {
            auto writer_element = writers_element->InsertNewChildElement("writer");
            writer_element->SetAttribute("name",d.c_str());
        }
    }
    doc.SaveFile(filename);
}





int main()
{
    std::vector<movie> res = xml_to_movies("pr73.xml");

    
    for (auto m : res)
    {
        std::cout << "id: " << m.id << std::endl;
        std::cout << "title: " << m.title << std::endl;
        for (auto p : m.directors)
        {
            std::cout << "director: " << p << std::endl;
        }
        for (auto p : m.casts)
        {
            std::cout << "cast " << p.first << " " << p.second << std::endl;
        }
    }

    movies_to_xml("pr73out.xml",res);
}
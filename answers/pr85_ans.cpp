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


#include <sqlite3.h>
#include "sqlite_modern_cpp/sqlite_modern_cpp.h"

struct casting_role
{
    std::string actor;
    std::string role;
};

struct movie
{
    unsigned int id;
    std::string title;
    int year;
    unsigned int length;
    std::vector<casting_role> cast;
    std::vector<std::string> directors;
    std::vector<std::string> writers;
};
using movie_list = std::vector<movie>;


std::vector<std::string> get_directors(sqlite3_int64 const movie_id,
                                       sqlite::database & db)
{
    std::vector<std::string> result;
    db << R"(select p.name from directors as w
          join persons as p on w.personid = p.rowid
          where w.movieid = ?;)"
       << movie_id 
       >> [& result] (std::string const name)
       {
           result.emplace_back(name);
       };
    return result;
}

std::vector<std::string> get_writers(sqlite3_int64 const movie_id,
                                     sqlite::database & db)
{
    std::vector<std::string> result;
    db << R"(select p.name from writers as w
          join persons as p on w.personid = p.rowid
          where w.movieid = ?;)"
       << movie_id 
       >> [& result] (std::string const name)
       {
           result.emplace_back(name);
       };
    return result;
}            

std::vector<casting_role> get_cast(sqlite3_int64 const movie_id,
                                   sqlite::database& db)
{
    std::vector<casting_role> result;
    db  << R"(select p.name, c.role from casting as c
           join persons as p on c.personid = p.rowid
           where c.movieid = ?;)"
        << movie_id 
        >> [& result] (std::string const name, std::string const role)
        {
            result.emplace_back(casting_role{name,role});
        };
    return result;
}

movie_list get_movies(sqlite::database& db)
{
    movie_list movies;

    db  << R"(select rowid, * from movies;)"
        >> [&movies, &db] (sqlite3_int64 const rowid,
                          std::string const title,
                          sqlite3_int64 const year,
                          sqlite3_int64 const length)
        {
            movies.emplace_back(
                movie{
                    static_cast<unsigned>(rowid),
                    title,
                    year,
                    static_cast<unsigned>(length),
                    get_cast(rowid,db),
                    get_directors(rowid,db),
                    get_writers(rowid,db)
                }
            );
        };
    return movies;
}

void print_movie(movie const& m)
{
    std::cout << "[" << m.id << "]\n";
    std::cout << " title    : " << m.title << std::endl;
    std::cout << " year     : " << m.year << std::endl;
    std::cout << " length   : " << m.length << std::endl;
    std::cout << " cast     : " << std::endl;
    for (auto const& c : m.cast)
        std::cout << "    role: " << c.role << " name: " << c.actor << std::endl;
    std::cout << " directors: " << std::endl;
    for (auto const& s : m.directors)
        std::cout << "    " << s << std::endl;
    std::cout << " writers  : " << std::endl;
    for (auto const& s : m.writers)
        std::cout << "    " << s << std::endl;
}

int main() 
{
    try
    {
        sqlite::database db("pr85.db");
        auto const movies = get_movies(db);
        for (auto const& m : movies)
        {
            print_movie(m);
        }
    }
    catch (sqlite::sqlite_exception const& e)
    {
        std::cerr << e.get_code() << std::endl;
    }
    catch (std::exception const& e)
    {
        std::cerr << e.what() << std::endl;
    }
}

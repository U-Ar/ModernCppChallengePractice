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


template<class Elem>
using tstring = std::basic_string<Elem, std::char_traits<Elem>,std::allocator<Elem>>;

template<class Elem>
using tstringstream = std::basic_stringstream<Elem, std::char_traits<Elem>,std::allocator<Elem>>;

template<typename Elem>
inline std::vector<tstring<Elem>> split(tstring<Elem> text, Elem const delimiter)
{
    auto sstr = tstringstream<Elem>{text};
    auto tokens = std::vector<tstring<Elem>>{};
    auto token = tstring<Elem>{};
    while (std::getline(sstr,token,delimiter))
    {
        if (!token.empty()) tokens.push_back(token);
    }
    return tokens;
}


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


movie read_movie()
{
    movie m;

    std::cout << "Enter movie" << std::endl;
    std::cout << "Title: ";
    std::getline(std::cin, m.title);

    std::cout << "Year: "; std::cin >> m.year;
    std::cout << "Length: "; std::cin >> m.length;
    std::cin.ignore();

    std::string directors;
    std::cout << "Directors: ";
    std::getline(std::cin, directors);
    m.directors = split(directors, ',');

    std::string writers;
    std::cout << "Writers: ";
    std::getline(std::cin, writers);
    m.writers = split(writers, ',');

    std::string cast;
    std::cout << "Cast: ";
    std::getline(std::cin, cast);
    auto roles = split(cast,',');
    for (auto const& r : roles)
    {
        auto const pos = r.find_first_of('=');
        casting_role cr;
        cr.actor = r.substr(0,pos);
        cr.role = r.substr(pos+1,r.size()-pos-1);
        m.cast.emplace_back(cr);
    }
    return m;
}

sqlite_int64 get_person_id(std::string const& name, sqlite::database& db)
{
    sqlite_int64 id = 0;
    db << "select rowid from persons where name=?"
       << name
       >> [&id](sqlite_int64 const rowid) {id = rowid;};
    return id;
}

sqlite_int64 get_movie_id(std::string const& name, sqlite::database& db)
{
    sqlite_int64 id = 0;
    db << "select rowid from movies where name=?"
       << name
       >> [&id](sqlite_int64 const rowid) {id = rowid;};
    return id;
}

sqlite_int64 insert_person(std::string const& name, sqlite::database& db)
{
    db  << "insert into persons values(?);"
        << name;
    return db.last_insert_rowid();
}

void insert_directors(sqlite_int64 const movie_id,
                      std::vector<std::string> const& directors,
                      sqlite::database& db)
{
    for (auto const& director : directors)
    {
        auto id = get_person_id(director,db);
        if (id == 0)
            id = insert_person(director,db);
        db  << "insert into directors values(?, ?);"
            << movie_id
            << id;
    }
}

void insert_writers(sqlite_int64 const movie_id,
                      std::vector<std::string> const& writers,
                      sqlite::database& db)
{
    for (auto const& writer : writers)
    {
        auto id = get_person_id(writer,db);
        if (id == 0)
            id = insert_person(writer,db);
        db  << "insert into writers values(?, ?);"
            << movie_id
            << id;
    }
}

void insert_cast(sqlite_int64 const movie_id,
                      std::vector<casting_role> const& cast,
                      sqlite::database& db)
{
    for (auto const& cr : cast)
    {
        auto id = get_person_id(cr.actor,db);
        if (id == 0)
            id = insert_person(cr.actor,db);
        db  << "insert into writers values(?, ?, ?);"
            << movie_id
            << id
            << cr.role;
    }
}

void insert_movie(movie& m, sqlite::database& db)
{
    try
    {
        db << "begin;";

        db << "insert into movies values(?,?,?)"
           << m.title
           << m.year 
           << m.length;
        
        auto movieid = db.last_insert_rowid();

        insert_directors(movieid,m.directors,db);
        insert_writers(movieid,m.writers,db);
        insert_cast(movieid,m.cast,db);

        m.id = static_cast<unsigned int>(movieid);

        db << "commit;";
    }
    catch (std::exception const& )
    {
        db << "rollback;";
    }
}

void insert_media(std::string const& movie, 
                  std::string const& filename, 
                  std::string const& description,
                  sqlite::database& db)
{
    std::ifstream ifs(filename,std::ios::binary);
    if (!ifs.is_open()) throw std::runtime_error("cannot open file");

    auto movieid = get_movie_id(movie,db);

    ifs.seekg(0,std::ios::end);
    auto len = ifs.tellg();
    ifs.seekg(0,std::ios::beg);

    char* buff = new char [len];
    ifs.read(buff, len);
    ifs.close();

    db  << "insert into media values (?, ?, ?, ?);"
        << movieid
        << filename
        << description
        << buff;
    delete buff;
}


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

        std::cout << "input datum of a movie:" << std::endl;
        movie tmp;
        tmp.info(std::cin);
        add_movie(tmp,db);
        
        auto const movies = get_movies(db);
        for (auto const& m : movies)
        {
            print_movie(m);
        }
    }
    catch (sqlite::sqlite_exception const& e)
    {
        std::cerr << e.get_code() << ": " << e.what() << " during "
                  << e.get_sql() << std::endl;
    }
    catch (std::exception const& e)
    {
        std::cerr << e.what() << std::endl;
    }
}

#include<iostream>
#include<sstream>
#include<string>
#include<algorithm>
#include<iterator>
#include<cmath>
#include<cassert>
#include<array>
#include<vector>
#include<iomanip>
#include<locale>
#include<regex> //regexヘッダで正規表現
#include<optional> //optional(C++17)
#include<ios>
#include<iomanip>
#include<fstream>
#include<chrono>

#include<filesystem>

#include <boost/uuid>

namespace fs = std::filesystem;
using namespace boost::uuids;

class logger {
    fs::path logpath;
    std::ofstream logfile;
public:
    logger()
    {
        auto name = lexical_cast<std::string>(random_generator()());
        logpath = fs::temp_directory_path() / (name+".tmp");
        logfile.open(logpath.c_str(),std::ios::out | std::ios::trunc);
    }

    ~logger() noexcept 
    {
        try {
            if (logfile.is_open()) logfile.close();
            if (!logpath.empty()) fs::remove(logpath);
        }
        catch(...) {}
    }

    void persist(fs::path const & path)
    {
        logfile.close();
        fs::rename(logpath, path);
        logpath.clear();
    }

    logger& operator<<(std::string const & message)
    {
        logfile << message.c_str() << '\n';
        return *this;
    }
};


int main() 
{
    logger log;
    try 
    {
        log << "this is a line" << "and this is another one";
        throw std::runtime_error("error");
    }
    catch (...)
    {
        log.persist(R"(lastlog.txt)");
    }
}

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

#include<experimental/filesystem>

namespace fs = std::experimental::filesystem;


class textlog {
    static int logs ;
    int id;
    fs::path path;
public:
    explicit textlog(std::string const log, fs::path const p) {
        logs++;
        id = logs;
        path = p;
        std::ofstream os(path,std::ios::out|std::ios::trunc);
        os << log;
        os.close();
    }
    ~textlog() {
        fs::remove(path);
    }
    void save(fs::path const & p) {
        fs::copy(path, p);
    }
    int get_id() {
        return id;
    }
    fs::path get_path() {
        return path;
    }
};


int textlog::logs = 0;

int main() 
{
    textlog log("this is tmp log.", fs::path("./tmp/log.txt"));
    std::cout << log.get_id() << " " << log.get_path().filename() << std::endl;
    log.save(fs::path("./per/log.txt"));
}

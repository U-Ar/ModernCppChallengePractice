
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
namespace ch = std::chrono;

template <typename Duration>
bool is_older_than(fs::path const & path, Duration const duration)
{
    auto ftimeduration = fs::last_write_time(path).time_since_epoch();
    auto nowduration = (ch::system_clock::now()-duration).time_since_epoch();
    return ch::duration_cast<Duration>(nowduration-ftimeduration).count() > 0;
}

template <typename Duration>
void remove_files_older_than(fs::path const & path, Duration const duration)
{
    try
    {
        if (fs::exists(path))
        {
            if (is_older_than(path,duration))
            {
                fs::remove_all(path);
            }
            else if (fs::is_directory(path))
            {
                for (auto const & entry : fs::directory_iterator(path))
                {
                    remove_files_older_than(entry.path(), duration);
                }
            }
        }
    }
    catch(std::exception const & ex)
    {
        std::cerr << ex.what() << std::endl;
    }
}

int main() 
{
    std::string s;
    std::cin >> s;
    using namespace std::chrono_literals;
    remove_files_older_than(s, 1s);
    
}

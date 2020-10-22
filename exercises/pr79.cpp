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
#include<regex>
#include<set>
#include<sstream>
#include<string>
#include<string_view>
#include<thread>
#include<type_traits>
#include<utility>
#include<vector>

#include"ziplib/ZipArchive.h"
#include"ziplib/ZipFile.h"
#include"ziplib/ZipArchiveEntry.h"


namespace fs = std::filesystem;

std::vector<std::string> find_in_archive(fs::path const& archivepath,
                                         std::string const& pattern)
{
    std::vector<std::string> results;
    if (fs::exists(archivepath))
    {
        try{
            auto archive = ZipFile::Open(archivepath.string());
            for (size_t i = 0, size = archive->GetEntriesCount(); i < size; ++i)
            {
                auto entry = archive->GetEntry(i);
                if (entry != nullptr)
                {
                    if (!entry->IsDirectory())
                    {
                        auto name = entry->GetName();
                        if (std::regex_match(name,std::regex{pattern.c_str()}))
                        {
                            results.push_back(entry->GetFullName());
                        }
                    }
                }
            }
        }
        catch(std::exception const& ex)
        {
            std::cout << ex.what() << std::endl;
        }
    }
    return results;
}

int main()
{
    auto results = find_in_archive("sample79.zip",R"(^.*\.jpg$)");
    for (auto const& name : results)
    {
        std::cout << name << std::endl;
    }
}
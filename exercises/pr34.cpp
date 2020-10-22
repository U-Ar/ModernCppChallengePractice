
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

#include<experimental/filesystem>

namespace fs = std::experimental::filesystem;
void remove_empty_lines(fs::path filepath)
{
    std::ifstream filein(filepath.native(),std::ios::in);
    if (!filein.is_open()) throw std::runtime_error("cannot open input file");
    auto temppath = fs::temp_directory_path() / "temp.txt";
    std::ofstream fileout(temppath.native(), std::ios::out | std::ios::trunc);
    if (!fileout.is_open())
        throw std::runtime_error("cannot create temporary file");
    std::string line;
    while (std::getline(filein, line))
    {
        if (line.length() > 0 && line.find_first_not_of(' ') != line.npos)
        {
            fileout << line << '\n';
        }
    } 

    filein.close();
    fileout.close();

    //元のファイルを削除
    fs::remove(filepath);
    //一時ファイルの名前を元のファイルの名前に書き換え
    fs::rename(temppath, filepath);
}

int main() 
{
    std::string s;
    std::cin >> s;
    remove_empty_lines(fs::path(s));
}

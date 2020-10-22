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


#include "crypto++/sha.h"
#include "crypto++/md5.h" 
#include "crypto++/hex.h" 
#include "crypto++/files.h" 
#include "crypto++/default.h" 

namespace fs = std::filesystem;

void encrypt_file(fs::path const& sourcefile,
                  fs::path const& destfile,
                  std::string const& password)
{
    CryptoPP::FileSource source(
        sourcefile.c_str(),
        true,
        new CryptoPP::DefaultEncryptorWithMAC(
            (byte*)password.c_str(),password.size(),
            new CryptoPP::FileSink(destfile.c_str())
        )
    );
}

void encrypt_file(fs::path const& filepath,
                  std::string const& password)
{
    auto temppath = fs::temp_directory_path() / filepath.filename();

    encrypt_file(filepath,temppath,password);

    fs::remove(filepath);
    fs::rename(temppath,filepath);
}


void decrypt_file(fs::path const& sourcefile,
                  fs::path const& destfile,
                  std::string const& password)
{
    CryptoPP::FileSource source(
        sourcefile.c_str(),
        true,
        new CryptoPP::DefaultDecryptorWithMAC(
            (byte*)password.c_str(),password.size(),
            new CryptoPP::FileSink(destfile.c_str())
        )
    );
}

void decrypt_file(fs::path const& filepath,
                  std::string const& password)
{
    auto temppath = fs::temp_directory_path() / filepath.filename();

    decrypt_file(filepath,temppath,password);

    fs::remove(filepath);
    fs::rename(temppath,filepath);
}


int main()
{
    encrypt_file("hist.png","hist.png.enc","myhist");
    decrypt_file("hist.png.enc","hist_decoded.png","myhist");
}
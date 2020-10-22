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

namespace fs = std::filesystem;

template <class Hash>
std::string compute_hash(fs::path const & filepath)
{
    std::ifstream file(filepath.string(), std::ios::binary);
    if (file.is_open())
    {
        Hash hash;
        byte digest[Hash::DIGESTSIZE] = { 0 };

        do
        {
            char buffer[4096] = { 0 };
            file.read(buffer, 4096);

            auto extracted = static_cast<size_t>(file.gcount());

            if (extracted > 0)
            {
            hash.Update(
                reinterpret_cast<byte*>(buffer),
                extracted);
            }
        } while (!file.fail());

        hash.Final(digest);

        CryptoPP::HexEncoder encoder;
        std::string result;

        encoder.Attach(new CryptoPP::StringSink(result));
        encoder.Put(digest, sizeof(digest));
        encoder.MessageEnd();

        return result;
    }

    throw std::runtime_error("Cannot open file!");
}

int main()
{
    std::string path;
    std::cout << "path: ";
    std::cin >> path;

    try 
    {
        std::cout << "SHA1:   "
        << compute_hash<CryptoPP::SHA1>(path) << std::endl;
        std::cout << "SHA256: "
        << compute_hash<CryptoPP::SHA256>(path) << std::endl;
        std::cout << "MD5:    "
        << compute_hash<CryptoPP::MD5>(path) << std::endl;
    
    }
    catch (std::exception const& ex)
    {
        std::cerr << ex.what() << std::endl;
    }
}
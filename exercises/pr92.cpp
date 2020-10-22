#include<bitset>
#include<cassert>
#include<chrono>
#include<cmath>
#include<cstddef>
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
#include<string_view>
#include<thread>
#include<type_traits>
#include<utility>
#include<vector>


#include "crypto++/sha.h"
#include "crypto++/md5.h" 
#include "crypto++/hex.h" 



void filehash(std::string const& filename)
{
    std::ifstream ifs(filename);
    if (!ifs)
    {
        std::cout << "Such file doesnt exist." << std::endl;
        return;
    }
    ifs.seekg(0, std::ios::end);
    std::string data;
    while(!ifs.eof()) {
        std::string tmp; ifs >> tmp;
        data += tmp;
    }

    CryptoPP::SHA1 sha;
    byte digest[CryptoPP::SHA1::DIGESTSIZE];

    sha.CalculateDigest(
        digest,
        reinterpret_cast<byte const*>(data.data()),
        data.length());

    CryptoPP::HexEncoder encoder;
    std::string result;

    encoder.Attach(new CryptoPP::StringSink(result));
    encoder.Put(digest, sizeof(digest));
    encoder.MessageEnd();

    std::cout << result << std::endl;
    result.clear(); 




    CryptoPP::SHA256 sha256;
    byte digest2[CryptoPP::SHA256::DIGESTSIZE];
    sha256.CalculateDigest(
        digest2,
        reinterpret_cast<byte const*>(data.data()),
        data.length());

    encoder.Attach(new CryptoPP::StringSink(result));
    encoder.Put(digest2, sizeof(digest));
    encoder.MessageEnd();

    std::cout << result << std::endl;
    result.clear();




    CryptoPP::MD5 md5;
    byte digest3[CryptoPP::MD5::DIGESTSIZE];
    md5.CalculateDigest(
        digest3,
        reinterpret_cast<byte const*>(data.data()),
        data.length());

    encoder.Attach(new CryptoPP::StringSink(result));
    encoder.Put(digest3, sizeof(digest3));
    encoder.MessageEnd();

    std::cout << result << std::endl;
    result.clear();

}

int main()
{

    filehash("pr60.cpp");
}
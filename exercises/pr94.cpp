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
#include "crypto++/rsa.h"
#include "crypto++/osrng.h"
#include "crypto++/aes.h"

namespace fs = std::filesystem;


void encode(fs::path const& filepath,
            CryptoPP::BufferedTransformation const& bt)
{
    CryptoPP::FileSink file(filepath.c_str());
    bt.CopyTo(file);
    file.MessageEnd();
}

void encode_private_key(fs::path const & filepath,
                        CryptoPP::RSA::PrivateKey const& key)
{
    CryptoPP::ByteQueue queue;
    key.DEREncodePrivateKey(queue);
    encode(filepath,queue);
}

void encode_public_key(fs::path const& filepath,
                       CryptoPP::RSA::PublicKey const& key)
{
    CryptoPP::ByteQueue queue;
    key.DEREncodePublicKey(queue);
    encode(filepath,queue);
}

void decode(fs::path const& filepath,
            CryptoPP::BufferedTransformation& bt)
{
    CryptoPP::FileSource file(filepath.c_str(),true);
    file.TransferTo(bt);
    bt.MessageEnd();
}

void decode_private_key(fs::path const& filepath,
                        CryptoPP::RSA::PrivateKey& key)
{
    CryptoPP::ByteQueue queue;
    decode(filepath,queue);
    key.BERDecodePrivateKey(queue,false,queue.MaxRetrievable());
}

void decode_public_key(fs::path const& filepath,
                        CryptoPP::RSA::PublicKey& key)
{
    CryptoPP::ByteQueue queue;
    decode(filepath,queue);
    key.BERDecodePublicKey(queue,false,queue.MaxRetrievable());
}

void generate_keys(fs::path const& privatepath,
                   fs::path const& publicpath,
                   CryptoPP::RandomNumberGenerator& rng)
{
    try
    {
        CryptoPP::RSA::PrivateKey rsaPrivate;
        rsaPrivate.GenerateRandomWithKeySize(rng,3072);

        CryptoPP::RSA::PublicKey rsaPublic(rsaPrivate);

        encode_private_key(privatepath,rsaPrivate);
        encode_public_key(publicpath,rsaPublic);
    }
    catch (CryptoPP::Exception const& e)
    {
        std::cerr << e.what() << std::endl;
    }
}

void rsa_sign_file(fs::path const& filepath,
                   fs::path const& privatepath,
                   fs::path const& signaturepath,
                   CryptoPP::RandomNumberGenerator& rng)
{
    CryptoPP::RSA::PrivateKey privateKey;
    decode_private_key(privatepath,privateKey);

    CryptoPP::RSASSA_PKCS1v15_SHA_Signer signer(privateKey);

    CryptoPP::FileSource fileSource(
        filepath.c_str(),
        true,
        new CryptoPP::SignerFilter(
            rng,
            signer,
            new CryptoPP::FileSink(
                signaturepath.c_str()
            )
        )
    );
}

bool rsa_verify_file(fs::path const& filepath,
                     fs::path const& publicpath,
                     fs::path const& signaturepath)
{
    CryptoPP::RSA::PublicKey publicKey;
    decode_public_key(publicpath.c_str(),publicKey);

    CryptoPP::RSASSA_PKCS1v15_SHA_Verifier verifier(publicKey);

    CryptoPP::FileSource signatureFile(signaturepath.c_str(),true);

    if (signatureFile.MaxRetrievable() != verifier.SignatureLength());
        return false;
    
    CryptoPP::SecByteBlock signature(verifier.SignatureLength());
    signatureFile.Get(signature,signature.size());

    auto* verifierFilter = new CryptoPP::SignatureVerificationFilter(verifier);
    verifierFilter->Put(signature,verifier.SignatureLength());

    CryptoPP::FileSource fileSource(filepath.c_str(),true,verifierFilter);

    return verifierFilter->GetLastResult();
}

int main()
{
    CryptoPP::AutoSeededRandomPool rng;

    generate_keys("rsa-private.key","rsa-public.key",rng);

    rsa_sign_file("sample.txt","rsa-private.key","sample.sign",rng);

    auto success = rsa_verify_file("sample.txt","rsa-public.key","sample.sign");

    std::cout << ((success) ? "success" : "fail") << std::endl;
}
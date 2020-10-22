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
#include"ziplib/utils/stream_utils.h"


namespace fs = std::filesystem;

void compress(fs::path const& source,
              fs::path const& archive,
              std::string const& password,
              std::function<void(std::string_view)> reporter)
{
    if (fs::is_regular_file(source))
    {
        if (reporter != nullptr) reporter("Compressing "+source.string());
        ZipFile::AddEncryptedFile(
            archive.string(),
            source.string(),
            source.filename().string(),
            password.c_str(),
            LzmaMethod::Create()
        );
    } 
    else 
    {
        for (auto const& p : fs::recursive_directory_iterator(source))
        {
            if (reporter != nullptr) reporter("Compressing " + p.path().string());
            if (fs::is_directory(p))
            {
                auto ziparchive = ZipFile::Open(archive.string());
                auto entry = ziparchive->CreateEntry(p.path().string());
                entry->SetAttributes(ZipArchiveEntry::Attributes::Directory);
                ZipFile::SaveAndClose(ziparchive,archive.string());
            }
            else if (fs::is_regular_file(p))
            {
                ZipFile::AddEncryptedFile(
                    archive.string(),
                    p.path().string(),
                    p.path().filename().string(),
                    password.c_str(),
                    LzmaMethod::Create()
                );
            }
        }
    }
}

void ensure_directory_exists(fs::path const& dir)
{
    if (!fs::exists(dir))
    {
        std::error_code err;
        fs::create_directories(dir,err);
    }
}

void decompress(fs::path const& destination,
                fs::path const& archive,
                std::string const& password,
                std::function<void(std::string_view)> reporter)
{
    ensure_directory_exists(destination);

    auto zipArchive = ZipFile::Open(archive.string());

    for (size_t i = 0; i < zipArchive->GetEntriesCount(); ++i)
    {
        auto entry = zipArchive->GetEntry(i);
        if (entry != nullptr)
        {
            auto filepath = destination /
                fs::path{entry->GetFullName()}.relative_path();
            if (reporter != nullptr) reporter("Creating "+filepath.string());

            if (entry->IsPasswordProtected())
                entry->SetPassword(password.c_str());

            if (entry->IsDirectory())
            {
                ensure_directory_exists(filepath);
            }
            else 
            {
                ensure_directory_exists(filepath.parent_path());
                std::ofstream destFile;

                destFile.open(filepath.string().c_str(),
                    std::ios::binary | std::ios::trunc);
                if (!destFile.is_open())
                {
                    if (reporter != nullptr)
                        reporter("Cannot create destination file!");
                }

                auto dataStream = entry->GetDecompressionStream();
                if (dataStream != nullptr)
                {
                    utils::stream::copy(*dataStream,destFile);
                }
            }
        }
    }
}

int main()
{
   char option = 0;
   std::cout << "Select [c]ompress/[d]ecompress?";
   std::cin >> option;

   if (option == 'c')
   {
      std::string archivepath;
      std::string inputpath;
      std::cout << "Enter file or dir to compress:";
      std::cin >> inputpath;
      std::cout << "Enter archive path:";
      std::cin >> archivepath;

      compress(inputpath, archivepath, [](std::string_view message) {std::cout << message << std::endl; });
   }
   else if (option == 'd')
   {
      std::string archivepath;
      std::string outputpath;
      std::cout << "Enter dir to decompress:";
      std::cin >> outputpath;
      std::cout << "Enter archive path:";
      std::cin >> archivepath;

      decompress(outputpath, archivepath, [](std::string_view message) {std::cout << message << std::endl; });
   }
   else
   {
      std::cout << "invalid option" << std::endl;
   }
}
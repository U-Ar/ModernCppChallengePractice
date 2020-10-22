#include<cassert>
#include<chrono>
#include<cmath>
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
#include<random>
#include<set>
#include<sstream>
#include<string>
#include<thread>
#include<type_traits>
#include<utility>
#include<vector>

enum class sex_type { female, male};

class Social_number_generator
{
protected:
    std::map<int, unsigned> cache;
    std::mt19937 eng;
    std::uniform_int_distribution<> ud;

    virtual int sex_digit(sex_type const sex) const noexcept = 0;
    virtual int next_random(unsigned int const year,
                            unsigned int const month,
                            unsigned int const day) = 0;
    virtual int modulo_value() const noexcept = 0;
    Social_number_generator(int const min, int const max)
    {
        std::random_device rd;
        auto seed_data = std::array<int, std::mt19937::state_size> {};
        std::generate(seed_data.begin(),seed_data.end(),std::ref(rd));
        std::seed_seq seq(seed_data.cbegin(),seed_data.cend());
        eng.seed(seq);
    }

public:
    std::string generate(sex_type const ex,
                         unsigned int const year,
                         unsigned int const month,
                         unsigned int const day)
    {
        std::stringstream ss;
        ss << sex_digit(ex)
           << std::setfill('0') << std::setw(4) << std::right 
           << year
           << std::setfill('0') << std::setw(2) << std::right 
           << month
           << std::setfill('0') << std::setw(2) << std::right 
           << day
           << next_random(year, month, day);

        auto const number = ss.str();
        auto index = number.size();
        auto const sum = std::accumulate(number.begin(),
            number.end(), 0U, 
            [&index](unsigned int const acc, char const c)
            {
                return acc + static_cast<unsigned>(index--)*(c-'0');
            });
        auto const rest = sum % modulo_value();
        ss << modulo_value() - rest;
        return ss.str();
    }
    virtual ~Social_number_generator() = default;
};

class Northeria_number_generator : public Social_number_generator
{
    virtual int sex_digit(sex_type const sex) const noexcept override 
    {
        return (sex == sex_type::male) ? 9 : 7;
    }
    virtual int next_random(unsigned int const year,
                            unsigned int const month,
                            unsigned int const day) override 
    {
        auto const key = year * 10000 + month * 100 + day;
        while (true)
        {
            auto const num = ud(eng);
            auto const pos = cache.find(num);
            if (pos == std::end(cache))
            {
                if (pos->second != key)
                {
                    cache[num] = key;
                    return num;
                }
            }
        }
    }

    virtual int modulo_value() const noexcept override 
    { return 11; }
public:
    Northeria_number_generator() 
    : Social_number_generator(1000,9999) {}
};

class Southeria_number_generator : public Social_number_generator
{
    virtual int sex_digit(sex_type const sex) const noexcept override 
    {
        return (sex == sex_type::male) ? 2 : 1;
    }
    virtual int next_random(unsigned int const year,
                            unsigned int const month,
                            unsigned int const day) override 
    {
        auto const key = year * 10000 + month * 100 + day;
        while (true)
        {
            auto const num = ud(eng);
            auto const pos = cache.find(num);
            if (pos == std::end(cache))
            {
                if (pos->second != key)
                {
                    cache[num] = key;
                    return num;
                }
            }
        }
    }

    virtual int modulo_value() const noexcept override 
    { return 10; }
public:
    Southeria_number_generator() 
    : Social_number_generator(10000,99999) {}
};


class Social_number_generator_factory
{
    std::map<std::string, 
             std::unique_ptr<Social_number_generator>> generators;
public:
    Social_number_generator_factory()
    {
        generators["northeria"] = 
            std::make_unique<Northeria_number_generator>();
        generators["southeria"] =
            std::make_unique<Southeria_number_generator>();
    }
    Social_number_generator* get_generator(std::string const & s)
    {
        if (generators.find(s) != generators.end())
        {
            return generators[s].get();
        }
        throw std::runtime_error("invalid country name");
    }
};



int main() 
{
    Social_number_generator_factory factory;

    auto sn1 = factory.get_generator("northeria")->generate(
        sex_type::female, 2017, 12, 25);
    auto sn2 = factory.get_generator("northeria")->generate(
        sex_type::female, 2017, 12, 25);
    auto sn3 = factory.get_generator("northeria")->generate(
        sex_type::male, 2017, 12, 25);
    
    auto sn4 = factory.get_generator("southeria")->generate(
        sex_type::female, 2017, 12, 25);
    auto sn5 = factory.get_generator("southeria")->generate(
        sex_type::female, 2017, 12, 25);
    auto sn6 = factory.get_generator("southeria")->generate(
        sex_type::male, 2017, 12, 25);

    std::cout << sn1 << std::endl
              << sn2 << std::endl
              << sn3 << std::endl
              << sn4 << std::endl
              << sn5 << std::endl
              << sn6 << std::endl;

}
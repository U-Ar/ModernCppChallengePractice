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
#include<sstream>
#include<string>
#include<thread>
#include<type_traits>
#include<utility>
#include<vector>

class password_generator
{
public:
    virtual std::string generate() = 0;

    virtual std::string allowed_chars() const = 0;
    virtual size_t length() const = 0;
    virtual void add(std::unique_ptr<password_generator> generator) = 0;

    virtual ~password_generator() = default;
};


class basic_password_generator : public password_generator
{
    size_t const len;
public:
    explicit basic_password_generator(size_t const l) noexcept
    : len(l) {}

    virtual std::string generate() override
    {
        throw std::runtime_error("not implemented");
    }
    virtual size_t length() const noexcept override final { return len; }
    virtual void add(std::unique_ptr<password_generator>) override 
    { 
        throw std::runtime_error("not implemented");
    }
};

class digit_generator : public basic_password_generator
{
public:
    explicit digit_generator(size_t const l) noexcept 
    : basic_password_generator(l) {}
    virtual std::string allowed_chars() const override 
    {
        return "1234567890";
    }
};
class symbol_generator : public basic_password_generator
{
public:
    explicit symbol_generator(size_t const l) noexcept 
    : basic_password_generator(l) {}
    virtual std::string allowed_chars() const override 
    {
        return "!@#$%&*(){}[]?<>";
    }
};
class upper_letter_generator : public basic_password_generator
{
public:
    explicit upper_letter_generator(size_t const l) noexcept 
    : basic_password_generator(l) {}
    virtual std::string allowed_chars() const override 
    {
        return "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    }
};
class lower_letter_generator : public basic_password_generator
{
public:
    explicit lower_letter_generator(size_t const l) noexcept 
    : basic_password_generator(l) {}
    virtual std::string allowed_chars() const override 
    {
        return "abcdefghijklmnopqrstuvwxyz";
    }
};


class composite_password_generator : public password_generator
{
    std::vector<std::unique_ptr<password_generator>> generators;
    std::random_device rd;
    std::mt19937 eng;
    virtual std::string allowed_chars() const override 
    { throw std::runtime_error("not implemented"); }
    virtual size_t length() const override 
    { throw std::runtime_error("not implemented"); }
public:
    explicit composite_password_generator()
    {
        auto seed_data = std::array<int, std::mt19937::state_size> {};
        std::generate(seed_data.begin(),seed_data.end(),std::ref(rd));
        std::seed_seq seq(seed_data.cbegin(),seed_data.cend());
        eng.seed(seq);
    }

    virtual void add(std::unique_ptr<password_generator> ptr) override 
    {
        generators.push_back(std::move(ptr));
    }

    virtual std::string generate() override 
    {
        std::string password;
        for (auto& generator : generators)
        {
            std::string chars = generator->allowed_chars();
            std::uniform_int_distribution<> ud(0,static_cast<int>(chars.size()-1));
            for (size_t i = 0; i < generator->length(); ++i)
            {
                password += chars[ud(eng)];
            }
        }
        std::shuffle(std::begin(password), std::end(password), eng);

        return password;
    }
};

int main() 
{
    composite_password_generator generator;
    generator.add(std::make_unique<symbol_generator>(2));
    generator.add(std::make_unique<digit_generator>(2));
    generator.add(std::make_unique<upper_letter_generator>(2));
    generator.add(std::make_unique<lower_letter_generator>(4));

    auto const password = generator.generate();

    std::cout << password << std::endl;

}
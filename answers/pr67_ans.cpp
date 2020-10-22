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


class password_validator
{
public:
    virtual bool validate(std::string const& pass) = 0;
    virtual ~password_validator() = default;
};

class length_validator final : public password_validator 
{
    size_t length;
public:
    explicit length_validator(size_t const l) : length(l) {}
    virtual bool validate(std::string const& s) override
    {
        return s.size() >= length;
    }
};

class password_validator_decorator : public password_validator
{
    std::unique_ptr<password_validator> inner;
public:
    explicit password_validator_decorator(
        std::unique_ptr<password_validator> validator)
    : inner(std::move(validator)) {}

    virtual bool validate(std::string const& s) override
    {
        return inner->validate(s);
    }
};




class digit_password_validator final : public password_validator_decorator
{
public:
    explicit digit_password_validator(
        std::unique_ptr<password_validator> validator)
    : password_validator_decorator(std::move(validator)) {}

    virtual bool validate(std::string const& s) override
    {
        if (!password_validator_decorator::validate(s)) return false;
        return std::find_if(s.begin(),s.end(),isdigit) != s.end();
    }
};
class symbol_password_validator final : public password_validator_decorator
{
public:
    explicit symbol_password_validator(
        std::unique_ptr<password_validator> validator)
    : password_validator_decorator(std::move(validator)) {}

    virtual bool validate(std::string const& s) override
    {
        if (!password_validator_decorator::validate(s)) return false;
        return std::find_if(s.begin(),s.end(),ispunct) != s.end();
    }
};
class case_password_validator final : public password_validator_decorator
{
public:
    explicit case_password_validator(
        std::unique_ptr<password_validator> validator)
    : password_validator_decorator(std::move(validator)) {}

    virtual bool validate(std::string const& s) override
    {
        if (!password_validator_decorator::validate(s)) return false;
        return std::find_if(s.begin(),s.end(),isupper) != s.end() &&
               std::find_if(s.begin(),s.end(),islower) != s.end();
    }
};




int main() 
{
    auto validator1 = std::make_unique<digit_password_validator>(
        std::make_unique<length_validator>(8)
    );
    assert(validator1->validate("abs123!@#"));
    assert(!validator1->validate("abcde!@"));
    auto validator2 = std::make_unique<symbol_password_validator>(
        std::make_unique<case_password_validator>(
            std::make_unique<digit_password_validator>(
                std::make_unique<length_validator>(8)
            )
        )
    );
    assert(validator2->validate("Abc123!@#"));
    assert(!validator2->validate("Abc1234567"));
}
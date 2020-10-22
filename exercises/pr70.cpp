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

class Role 
{
public:
    virtual double approval_limit() const noexcept = 0;
    virtual ~Role() = default;
};

class Employee_role : public Role
{
    virtual double approval_limit() const noexcept override 
    { return 1000; }
};

class Team_manager_role : public Role
{
    virtual double approval_limit() const noexcept override 
    { return 10000; }
};

class Department_manager_role : public Role
{
    virtual double approval_limit() const noexcept override 
    { return 100000; }
};

class President_role : public Role 
{
    virtual double approval_limit() const noexcept override 
    { return std::numeric_limits<double>::infinity(); }
};

struct expense 
{
    double const amount;
    std::string const description;
    expense(double const a, std::string const& d)
    : amount(a), description(d) {}
};

class Employee
{
    std::string name;
    std::unique_ptr<Role> role;
    std::shared_ptr<Employee> direct_manager;
public:
    explicit Employee(std::string const& n, 
    std::unique_ptr<Role> r) 
    : name(n), role(std::move(r)) {}
    void set_manager(std::shared_ptr<Employee> dm)
    { direct_manager = dm; }

    void approve(expense const& e)
    {
        if ((*role).approval_limit() >= e.amount)
        {
            std::cout << name << " approved " 
                      << e.description 
                      << " for the expense of "
                      << e.amount << ".\n"; 
            return;
        }
        direct_manager->approve(e);
    }
};

int main() 
{
    auto john = std::make_shared<Employee>("john", 
    std::make_unique<Employee_role>());
    auto rob = std::make_shared<Employee>("rob", 
    std::make_unique<Team_manager_role>());
    auto cecil = std::make_shared<Employee>("cecil", 
    std::make_unique<Department_manager_role>());
    auto david = std::make_shared<Employee>("david", 
    std::make_unique<President_role>());

    john->set_manager(rob);
    rob->set_manager(cecil);
    cecil->set_manager(david);

    john->approve(expense{500, "magazines"});
    john->approve(expense{5000, "hotel accomodation"});
    john->approve(expense{50000, "conference costs"});
    john->approve(expense{20000000, "new lorry"});

}
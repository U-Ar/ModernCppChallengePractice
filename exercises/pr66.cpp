#include<array>
#include<cassert>
#include<chrono>
#include<cmath>
#include<cstdlib>
#include<ctime>
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

struct Customer {};

class Office
{
    std::vector<Customer> customers;
    std::vector<int> tickets;
    std::mutex mtx;
public:
    Office() : customers(0) {}
    
    void enter(std::vector<Customer> const& x)
    {
        customers += x;
    }

    void serve(Customer& c)
    {
        return;
    }

    void simulate()
    {
        tickets.resize(customers.size());
        for (int i = 1; i <= customers.size(); i++) tickets[i-1] = i;
        auto itr = customers.begin();
        auto t1 = std::thread([&](){ 
            while (true) {
                std::lock_guard<std::mutex> lock(mtx);
                if (itr == customers.end()) break;
                serve(*itr);
                itr++;
            }
        })
    }

};

int main()
{
    std::vector<int> customer
}
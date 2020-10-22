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



struct discount_type
{
    virtual double discount_percent(double const price,
        double const quantity) const noexcept = 0;
    virtual ~discount_type() = default;
};

struct fixed_discount : public discount_type
{
    double const discount;
public:
    explicit fixed_discount(double const discount) noexcept 
    : discount(discount) {}
    virtual double discount_percent(double const,
    double const) const noexcept {return discount;}
};

struct volume_discount : public discount_type
{
    double const discount;
    double const min_quantity;
public:
    explicit volume_discount(double const quantity,
                             double const discount) noexcept 
        : discount(discount), min_quantity(quantity) {}
    virtual double discount_percent(double const,
                                    double const quantity) const noexcept
    { return quantity >= min_quantity ? discount : 0; }
};

struct price_discount : public discount_type
{
    double const discount;
    double const min_total_price;
public:
    explicit price_discount(double const price,
                            double const discount) noexcept 
        : discount(discount), min_total_price(price) {}
    virtual double discount_percent(double const price,
                                    double const quantity) const noexcept
    { return price*quantity >= min_total_price ? discount : 0; }
};

struct amount_discount : public discount_type
{
    double const discount;
    double const min_total_price;
public:
    explicit amount_discount(double const price,
                            double const discount) noexcept 
        : discount(discount), min_total_price(price) {}
    virtual double discount_percent(double const price,
                                    double const) const noexcept
    { return price >= min_total_price ? discount : 0; }
};

struct customer
{
    std::string name;
    discount_type* discount;
};

enum class article_unit
{
    piece, kg, meter, sqmeter, cmeter, liter
};

struct article
{
    int id;
    std::string name;
    double price;
    article_unit unit;
    discount_type* discount;
};

struct order_line
{
    article product;
    int quantity;
    discount_type* discount;
};

struct order
{
    int id;
    customer* buyer;
    std::vector<order_line> lines;
    discount_type* discount;
};

struct price_calculator
{
    virtual double calculate_price(order const& o) = 0;
    virtual ~price_calculator() = default;
};

struct cumulative_price_calculator : public price_calculator
{
    virtual double calculate_price(order const& o) override 
    {
        double price = 0.0;

        for (auto ol : o.lines)
        {
            double line_price = ol.product.price * ol.quantity;

            if (ol.product.discount != nullptr)
                line_price *= (1.0-ol.product.discount->discount_percent(
                    ol.product.price, ol.quantity
                ));
            if (ol.discount != nullptr)
                line_price *= (1.0-ol.discount->discount_percent(
                    ol.product.price, ol.quantity
                ));
            if (o.buyer != nullptr && o.buyer->discount != nullptr)
                line_price *= (1.0-o.buyer->discount->discount_percent(
                    ol.product.price, ol.quantity
                ));
            price += line_price;
        }   
        
        if (o.discount != nullptr)
        {
            price *= (1.0-o.discount->discount_percent(price,0.0));
        }
        return price;
    }
};

inline bool are_equal(double const d1, double const d2,
                      double const diff = 0.001)
{
    return std::abs(d1-d2) <= diff;
}

int main()
{
    fixed_discount d1(0.1);
    volume_discount d2(10,0.15);
    price_discount d3(100,0.15);
    amount_discount d4(100, 0.05);

    customer c1 {"default", nullptr};
    customer c2 {"john", &d1};
    customer c3 {"joane", &d3};

    article a1 {1, "pen", 5, article_unit::piece, nullptr};
    article a2 {2, "expensive pen", 15, article_unit::piece, &d1};
    article a3 {3, "scissors", 10, article_unit::piece, &d2};

    cumulative_price_calculator calc;

    order o1 {101, &c1, {{a1, 1, nullptr}}, nullptr};
    assert(are_equal(calc.calculate_price(o1), 5.0));


}
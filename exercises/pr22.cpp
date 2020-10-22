#include<iostream>
#include<sstream>
#include<array>
#include<string>
#include<vector>
#include<algorithm>
#include<iterator>
#include<list>
#include<cassert>

namespace temps {

class Temp 
{
    double kelvin;
public:
    constexpr Temp() : kelvin(0) {}
    explicit constexpr Temp(double temp) : kelvin(temp) {}
    Temp(const Temp& other) noexcept : kelvin(other.kelvin) {}
    Temp& operator= (const Temp& other) {
        kelvin = other.kelvin;
        return *this;
    }

    double to_K() {
        return kelvin;
    }
    double to_f() {
        return 9.0*kelvin/5.0-459.67;
    }
    double to_deg() {
        return kelvin - 273.15;
    }


    friend bool operator<(Temp const & a, Temp const & b) {
        return a.kelvin < b.kelvin;
    }
    friend bool operator<=(Temp const & a, Temp const & b) {
        return a.kelvin <= b.kelvin;
    }
    friend bool operator>(Temp const & a, Temp const & b) {
        return a.kelvin > b.kelvin;
    }
    friend bool operator>=(Temp const & a, Temp const & b) {
        return a.kelvin >= b.kelvin;
    }
    friend bool operator==(Temp const & a, Temp const & b) {
        return a.kelvin == b.kelvin;
    }
    friend bool operator!=(Temp const & a, Temp const & b) {
        return a.kelvin != b.kelvin;
    }
    friend Temp operator+(Temp const & a, Temp const & b) {
        return Temp(a.kelvin + b.kelvin);
    }
    friend Temp operator-(Temp const & a, Temp const & b) {
        return Temp(a.kelvin - b.kelvin);
    }

    friend std::ostream& operator<<(std::ostream& os, const Temp& a) {
        os << a.kelvin << "K";
        return os;
    }
    friend std::istream& operator>>(std::istream& is, Temp& temp) {
        double a;
        std::string b;
        std::cin >> a >> b;
        if (b == "K") {
            temp.kelvin = a;
        } else if (b == "F") {
            temp.kelvin = 5.0*(a + 459.67) / 9.0;
        } else if (b == "deg") {
            temp.kelvin = a * 273.15;
        } else {
            is.setstate(std::ios_base::failbit);
        }
        return is;
    }

};

Temp operator"" _deg(long double temp) {
    return Temp(temp + 273.15);
}

Temp operator"" _f(long double temp) {
    return Temp(5.0*(temp + 459.67) / 9.0);
}

Temp operator"" _K(long double temp) {
    return Temp(temp);
}

}

using namespace temps;
int main() {
    Temp a = 100.0_K;
    Temp b = 300.0_f;
    Temp c = 400.0_deg;
    std::cout << a + c << std::endl;
    std::cin >> c;
    std::cout << c << std::endl;
}
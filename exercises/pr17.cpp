#include<iostream>
#include<sstream>
#include<array>
#include<string>
#include<vector>
#include<algorithm>

template<class T, int M, int N>
class matrix {
    std::array<T, M*N> mat;
public:
    constexpr matrix() : matrix(std::array<T,M*N>(0)) {}
    constexpr matrix(const std::array<T, M*N>& a) {
        mat(a);
    }
    matrix(matrix const & other) noexcept : mat(other.mat) {}
    matrix& operator=(matrix const& other) noexcept {
        mat = other.mat;
        return *this;
    }
    T at(int x, int y) {
        return mat[x*N+y];
    }
    std::array<T, M*N> data() {
        return mat;
    }
    int capacity() {
        return M * N;
    }
    void fill(const T& a) {
        std::for_each(mat.begin(),mat.end(),[&a](T& b) { b = a; });
    }
    friend void swap(matrix const & a, matrix const & b) {
        std::swap(a.mat, b.mat);
    }

};

class ipv4 {
    std::array<unsigned char,4> mat;
public:
    constexpr ipv4() : ipv4(0,0,0,0) {}
    constexpr ipv4(unsigned char const a, unsigned char const b,
                unsigned char const c, unsigned char const d):
                mat{{a,b,c,d}} {}
    //値渡しなので他のコンストラクタが呼ばれないようexplicitをつける
    explicit constexpr ipv4(unsigned long a) :
    ipv4(static_cast<unsigned char>((a>>24) & 0xFF),
         static_cast<unsigned char>((a>>16) & 0xFF),
         static_cast<unsigned char>((a>>8) & 0xFF),
         static_cast<unsigned char>(a & 0xFF)) {}
    ipv4(ipv4 const & other) noexcept : mat(other.mat) {}
    ipv4& operator=(ipv4 const & other) noexcept {
        mat = other.mat;
        return *this;
    }

    std::string to_string() const {
        std::stringstream sstr;
        sstr << *this;
        return sstr.str();
    }

    constexpr unsigned long to_ulong() const noexcept {
        return 
        (static_cast<unsigned long>(mat[0]) << 24)|
        (static_cast<unsigned long>(mat[1]) << 16)|
        (static_cast<unsigned long>(mat[2]) << 8)|
        static_cast<unsigned long>(mat[3]);
    }

    friend std::ostream& operator<<(std::ostream& os, const ipv4& a) {
        os << static_cast<int>(a.mat[0]) << '.'
           << static_cast<int>(a.mat[1]) << '.'
           << static_cast<int>(a.mat[2]) << '.'
           << static_cast<int>(a.mat[3]);
    }

    friend std::istream& operator>>(std::istream& is, ipv4& a) {
        char d1, d2, d3;
        int b1, b2, b3, b4;
        is >> b1 >> d1 >> b2 >> d2 >> b3 >> d3 >> b4;
        if (d1 == '.' && d2 == '.' && d3 == '.') {
            a = ipv4(b1,b2,b3,b4);
        } else {
            is.setstate(std::ios_base::failbit);
        }
        return is;
    }
    
    //++ipv4
    ipv4& operator++() {
        *this = ipv4(1+to_ulong());
        return *this;
    }
    
    //ipv4++
    ipv4 operator++(int) {
        ipv4 result(*this);
        ++(*this);
        return result;
    }

    friend bool operator==(const ipv4& lhs, const ipv4& rhs) noexcept 
    {
        return lhs.mat == rhs.mat;
    }

    friend bool operator!=(const ipv4& lhs, const ipv4& rhs) noexcept 
    {
        return lhs.mat != rhs.mat;
    }

    friend bool operator<(const ipv4& lhs, const ipv4& rhs) noexcept   
    {
        return lhs.to_ulong() < rhs.to_ulong();
    }

    friend bool operator>(const ipv4& lhs, const ipv4& rhs) noexcept   
    {
        return lhs.to_ulong() > rhs.to_ulong();
    }

    friend bool operator<=(const ipv4& lhs, const ipv4& rhs) noexcept   
    {
        return lhs.to_ulong() <= rhs.to_ulong();
    }

    friend bool operator>=(const ipv4& lhs, const ipv4& rhs) noexcept   
    {
        return lhs.to_ulong() >= rhs.to_ulong();
    }


    
};

int main() {
    ipv4 a, b;
    std::cin >> a;
    std::cin >> b;
    if (b > a) {
        for (ipv4 i = a; i <= b; i++) {
            std::cout << i << std::endl;
        }
    } else {
        "Invalid range.\n";
    }
}
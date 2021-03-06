#include<iostream>
#include<sstream>
#include<array>
#include<string>

class ipv4 {
    std::array<unsigned char,4> data;
public:
    //constexprはコンパイル時に評価できる変数/関数につける
    constexpr ipv4() : ipv4(0,0,0,0) {}
    constexpr ipv4(unsigned char const a, unsigned char const b,
                unsigned char const c, unsigned char const d):
                data{{a,b,c,d}} {}
    explicit constexpr ipv4(unsigned long a) :
    ipv4(static_cast<unsigned char>((a>>24) & 0xFF),
         static_cast<unsigned char>((a>>16) & 0xFF),
         static_cast<unsigned char>((a>>8) & 0xFF),
         static_cast<unsigned char>(a & 0xFF)) {}
    //noexcept: 例外を送出しない関数
    ipv4(ipv4 const & other) noexcept : data(other.data) {}
    ipv4& operator=(ipv4 const & other) noexcept {
        data = other.data;
        return *this;
    }

    //関数名の後のconstは、関数内でのメンバ変数の変更を禁止する
    std::string to_string() const {
        std::stringstream sstr;
        sstr << *this;
        return sstr.str();
    }

    constexpr unsigned long to_ulong() const noexcept {
        return 
        (static_cast<unsigned long>(data[0]) << 24)|
        (static_cast<unsigned long>(data[1]) << 16)|
        (static_cast<unsigned long>(data[2]) << 8)|
        static_cast<unsigned long>(data[3]);
    }

    //入出力演算子オーバーロードはfriend関数で記述
    //フレンド関数は引数クラス内の非公開メンバを参照できる
    friend std::ostream& operator<<(std::ostream& os, const ipv4& a) {
        os << static_cast<int>(a.data[0]) << '.'
           << static_cast<int>(a.data[1]) << '.'
           << static_cast<int>(a.data[2]) << '.'
           << static_cast<int>(a.data[3]);
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
    
};

int main() {
    ipv4 address(168, 192, 0, 1);
    std::cout << address << std::endl;

    ipv4 ip;
    std::cout << ip << std::endl;
    std::cin >> ip;
    if (!std::cin.fail()) 
    std::cout << ip << std::endl;
}
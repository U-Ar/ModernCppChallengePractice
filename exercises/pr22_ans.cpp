/*
enumを利用してそれぞれが使っている温度システムを記録するようにする
temperature_castによるキャストを自分で定義する

実装するもの
温度単位の列挙型scale
scaleを引数とするクラステンプレートquantity(温度の実体)
2つのquantityを比較する比較演算子
同じ型のquantityの値の加減算を行う演算子、代入演算子
温度系の変更を行うcast
リテラル演算子
*/

#include<iostream>
#include<sstream>
#include<string>
#include<algorithm>
#include<iterator>
#include<cmath>
#include<cassert>

bool are_equal(double const d1, double const d2, double const epsilon=0.001)
{
    return std::fabs(d1-d2) < epsilon;
}



namespace temperature
{
    enum class scale { celsius, fahrenheit, kelvin };

    template <scale S>
    class quantity
    {
        double const amount;
    public:
        constexpr explicit quantity(double const a) : amount(a) {}
        //doubleキャスト演算子のオーバーロード
        explicit operator double() const { return amount; }
    };

    //比較演算
    template <scale S>
    inline bool operator==(quantity<S> const & lhs, quantity<S> const & rhs)
    {
        return are_equal(static_cast<double>(lhs), static_cast<double>(rhs));
    }
    template <scale S>
    inline bool operator!=(quantity<S> const & lhs, quantity<S> const & rhs)
    {
        return !(lhs==rhs);
    }
    template <scale S>
    inline bool operator<(quantity<S> const & lhs, quantity<S> const & rhs)
    {
        return static_cast<double>(lhs) < static_cast<double>(rhs);
    }
    template <scale S>
    inline bool operator>(quantity<S> const & lhs, quantity<S> const & rhs)
    {
        return static_cast<double>(lhs) > static_cast<double>(rhs);
    }
    template <scale S>
    inline bool operator<=(quantity<S> const & lhs, quantity<S> const & rhs)
    {
        return !(lhs > rhs);
    }
    template <scale S>
    inline bool operator>=(quantity<S> const & lhs, quantity<S> const & rhs)
    {
        return !(lhs < rhs);
    }
    
    //算術演算
    template <scale S>
    constexpr quantity<S> operator+(quantity<S> const & q1,
                                    quantity<S> const & q2)
    {
        return quantity<S>(static_cast<double>(q1)+static_cast<double>(q2));
    }
    template <scale S>
    constexpr quantity<S> operator-(quantity<S> const & q1,
                                    quantity<S> const & q2)
    {
        return quantity<S>(static_cast<double>(q1)-static_cast<double>(q2));
    }
    
    //temperature_castの定義
    //conversion_traitsは言語仕様ではない（絶対これに従えというものでない）
    //が、castの定義を系統立てて可能なので役立つ
    template <scale S, scale R>
    struct conversion_traits
    {
        //暗黙の定義の禁止？
        static double convert(double const value) = delete;
    };
    //template<>の意味...テンプレートの特殊化
    template<>
    struct conversion_traits<scale::celsius, scale::fahrenheit>
    {
        static double convert(double const value)
        {
            return (value * 9) / 5.0 + 32;
        }
    };
    template<>
    struct conversion_traits<scale::fahrenheit, scale::celsius>
    {
        static double convert(double const value)
        {
            return (value - 32) * 5 / 9.0;
        }
    };
    template<>
    struct conversion_traits<scale::celsius, scale::kelvin>
    {
        static double convert(double const value)
        {
            return value + 273.15;
        }
    };
    template<>
    struct conversion_traits<scale::kelvin, scale::celsius>
    {
        static double convert(double const value)
        {
            return value - 273.15;
        }
    };
    template<>
    struct conversion_traits<scale::kelvin, scale::fahrenheit>
    {
        static double convert(double const value)
        {
            return value * 9 / 5.0 - 459.67;
        }
    };
    template<>
    struct conversion_traits<scale::fahrenheit, scale::kelvin>
    {
        static double convert(double const value)
        {
            return (value + 459.67) * 5 / 9.0 ;
        }
    };

    template <scale R, scale S>
    constexpr quantity<R> temperature_cast(quantity<S> const q)
    {
        return quantity<R>(conversion_traits<S, R>::convert(
            static_cast<double>(q)));
    }
}

//他のリテラル演算子との名前重複を防ぐため、リテラルは別の名前空間に
//リテラルの引数として可能なのはlong doubleなど(仕様参照)
namespace temperature::temperature_scale_literals {
    constexpr quantity<scale::celsius> operator ""_deg(long double const amount)
    {
        return quantity<scale::celsius> {static_cast<double>(amount)};
    }
}

namespace temperature::temperature_scale_literals {
    constexpr quantity<scale::fahrenheit> operator ""_f(long double const amount)
    {
        return quantity<scale::fahrenheit> {static_cast<double>(amount)};
    }
}

namespace temperature::temperature_scale_literals {
    constexpr quantity<scale::kelvin> operator ""_K(long double const amount)
    {
        return quantity<scale::kelvin> {static_cast<double>(amount)};
    }
}


int main() {
    using namespace temperature;
    using namespace temperature::temperature_scale_literals;
    auto t1{ 36.5_deg };
    auto t2{ 341.1_K };
    auto t3{ 160.1_f };
    auto t4{ 20.1_f };

    auto tf = temperature_cast<scale::fahrenheit> (t1);
    auto tc = temperature_cast<scale::celsius> (tf);
    assert(t1 == tc);
    std::cout << static_cast<double>(t3+t4) << std::endl;
}

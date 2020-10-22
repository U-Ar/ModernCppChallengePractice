/*
自分の解答との違い
可変長の引数実装に必要なパラメータが一つ少なかった
関数の型指定に際して、テンプレートで気軽にCompと定義していた
*/
#include<iostream>

template<typename T>
T minimum(const T a, const T b) {
    if (a <= b) return a;
    return b;
}

template<typename T, typename... T1>
T minimum(const T a, const T1... b) {
    return minimum(a,minimum(b...));
}

template<typename Comp, typename T>
T minimum2(Comp comp, const T a, const T b) {
    if (comp(a,b)) return a;
    return b;
}

template<typename Comp, typename T, typename... T1>
T minimum2(Comp comp, const T a, const T1... b) {
    return minimum2(comp,a,minimum2(b...));
}

int main() {
    auto x = minimum(5,4,2,3);
    std::cout << x << std::endl;
}
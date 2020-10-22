/*
疑問　ムーブコンストラクタとかムーブ可能とか作る意味は？
　　　配列系の初期化方法に幅がありすぎでは？

TIPS　要求された構造をどう定義するか考えるまでに、まずテストケース作り
      std::arrayかvectorかの選択で検討する二点
      ・オブジェクトのムーブのためにムーブセマンティクスをサポートする
      ・オブジェクトのリスト初期化をサポートする
      これらが可能なのはvectorなのでvectorを使う
*/
#include<iostream>
#include<sstream>
#include<array>
#include<string>
#include<vector>
#include<algorithm>
#include<iterator>

template<class T, size_t R, size_t C>
class array2d {
    //分かりやすいよう再命名しただけ
    //iteratorの中身はTのポインタ！
    typedef T                 value_type;
    typedef value_type*       iterator;
    typedef value_type const* const_iterator;
    
    std::vector<T>            arr;

public:
    array2d() : arr(R*C) {}
    //initializer_lsit...ユーザ定義型が初期化子リスト構文による初期化を可能にするためのクラス
    explicit array2d(std::initializer_list<T> l) : arr(l) {}
    //data()...配列先頭へのポインタを取得する
    constexpr T* data() noexcept { return arr.data(); }
    constexpr T const * data() const noexcept { return arr.data(); }

    //インデックスの型はsize_t
    //アクセス系の演算子はconst版も作る
    constexpr T& at(size_t const r, size_t const c) {
        return arr.at(r*C+c);
    }

    constexpr T const & at(size_t const r, size_t const c) const {
        return arr.at(r*C+c);
    }

    constexpr T& operator() (size_t const r, size_t const c) {
        return arr[r*C+c];
    }

    constexpr T const & operator() (size_t const r, size_t const c) const {
        return arr[r*C+c];
    }

    constexpr bool empty() const noexcept { return R == 0 || C == 0; }

    //サイズのメンバ関数：1で行数、2で列数
    constexpr size_t size(int const rank) const 
    {
        if (rank == 1) return R;
        else if (rank == 2) return C;
        throw std::out_of_range("Rank is out of range!");
    }
    
    //もともとのコンテナにあるメソッドをそのまま使うと良い
    void fill(T const & value) {
        std::fill(std::begin(arr), std::end(arr), value);
    }
    
    //テンプレートの中では引数の中でも<T,R,C>とかやらなくてもよい
    void swap(array2d & other) noexcept { arr.swap(other.arr); }

    //data()で先頭のポインタを返すのでこれでよいらしい
    //イテレータを定義しろと言われたらこれ
    const_iterator begin() const { return arr.data(); }
    const_iterator end() const { return arr.data() + arr.size(); }
    iterator begin() { return arr.data(); }
    iterator end() { return arr.data() + arr.size(); }


};


int main() {
    //配列の行数と列数をテンプレートパラメータにするアイディアは
    //自分でもできた
    //operator()は複数の引数をとれるアクセス演算子らしい！
    //[]は引数を一つしか取れないので、使いたいなら中間の型が必要
    array2d<int, 2, 3> a {1, 2, 3, 4, 5, 6};
    for (size_t i = 0; i < a.size(1); i++) {
        for (size_t j = 0; j < a.size(2); j++) {
            a(i,j) *= 2;
        }
    }
    //std::copyは、指定範囲を第三引数のやつにコピーする
    //vectorの中身をprintしたりする動作は↓で書ける
    std::copy(std::cbegin(a),std::cend(a), 
    std::ostream_iterator<int>(std::cout, " "));

    //フィリング
    array2d<int, 2, 3> b;
    b.fill(1);

    //スワップ スワップはメンバ関数として書くのがよいぽい
    a.swap(b);

    //ムーブ
    array2d<int, 2, 3> c(std::move(b));
}
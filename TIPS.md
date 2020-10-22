# モダンC++チャレンジで学習した内容

## 問題18
* 可変長引数の書き方
例えば、任意個数の引数をとる最小値関数は以下のように再帰で書く
```c++
template<typename T>
T minimum(const T a, const T b) {
    if (a <= b) return a;
    return b;
}

template<typename T, typename... T1>
T minimum(const T a, const T1... b) {
    return minimum(a,minimum(b...));
}
```
* 関数を引数にとるテンプレートの書き方
```c++
//原始的な関数ポインタの書き方は
T (*func) (const T a, const T b)  

//テンプレートを活用すると
template<typename Comp, typename T>
T minimum2(Comp comp, const T a, const T b) {
    if (comp(a,b)) return a;
    return b;
}

template<typename Comp, typename T, typename... T1>
T minimum2(Comp comp, const T a, const T1... b) {
    return minimum2(comp,a,minimum2(b...));
}
```

## 問題19
可変長引数関数では、畳み込み式で短縮記法が使えることがある
```c++
template<typename C, typename... Args>
void push_back(C& c, Args&&... args) {
    //argsの後に続く...を外に出すことで一つずつの操作を示す
    (c.push_back(args), ...);
}
```

## 問題20
* 19と同じで畳み込み式で可変長引数を簡略化する
```c++
template<typename C, typename T>
bool contains_any(const C& container, const T& a) {
    return contains(container, a);
}
template<typename C, typename T, typename... T1>
bool contains_any(const C& container, const T& a, const T1... rest) {
    return contains(container, a) || contains_any(container, rest...);
}
```
を簡略化すると
```c++
template<class C, class T...>
bool contains_any(const C & container, T &&... value)
{
    return (... || contains(c, value));
}
```
* std::forwardの使い方
https://teratail.com/questions/282954 を参照
「完全転送した呼び出しにする」関数
```c++
//Fの引数がいちいちコピーされるのを避けたいため、
//右辺値の参照をそのまま受け取れるようにT&&とする
//std::forward<T>(v)とはvの参照元が右辺値ならvを右辺値に、
//vの参照元が左辺値ならvを左辺地にキャストする関数
template<class T> 
static void F(T&& v)
{
    f(std::forward<T>(v))
}
```

## 問題21
* RAIIを用いてハンドルの管理

## 問題22
* enum classを用いて登録した識別子は、呼び出し時にスコープ名が必須なので安全 これをテンプレート引数にして各温度系でのクラスを定義する
```c++
enum A { BLACK = 1, WHITE};
A ex1 = BLACK; //可能

enum class B { BLACK = 1, WHITE};
B ex2 = BLACK; //不可能
B ex3 = B::BLACK //可能
```
* 構造体conversion_traitsのstaticメンバ関数で温度系間の変換を定義するとcastは簡単に書ける
```c++
template <scale R, scale S>
constexpr quantity<R> temperature_cast(quantity<S> const q)
{
    return quantity<R>(conversion_traits<S, R>::convert(
                       static_cast<double>(q)));
}
```

## 問題23
ostringstreamに逐次文字列を書き込み、最後にoss.str()でstringが返せる

## 問題24 語頭大文字変換
stringに限らずほかのバイト長の文字列にも一般に使えるようにしたいなら
```c++
template <class Elem>
using tstring = std::basic_string<Elem, std::char_traits<Elem>, 
                                    std::allocator<Elem> >;
```
でbasic_stringの型を簡潔に表記できるようにしつつ
```c++
template <class Elem>
tstring<Elem> capitalize(tstring<Elem> const & text)
{
    tstringstream<Elem> result;
    bool newWord = true; 
    for (auto const ch : text)
    {
        newWord = newWord || std::ispunct(ch) || std::isspace(ch);
        if (std::isalpha(ch))
        {
            if (newWord)
            {
                result << static_cast<Elem> (std::toupper(ch));
                newWord = false;
            }
            else result << static_cast<Elem> (std::tolower(ch));
        }
        else result << ch;
    }
    return result.str();
}
```

## 問題26 単語連結のjoin
コンテナ全体で何かを行う関数テンプレートを作るなら、イテレータの開始-終了範囲を指定して行う関数をついでに作り、その特殊化として作ると良い

## 問題27 最長回文部分文字列

## 問題29 ナンバープレートの検証
正規表現を覚えるともっと楽になりそう

## 問題30 URLパース-正規表現
* std::optional<int> a などとすると、aが値を持たない状況も許される
オプショナルなデータメンバを表現するときなど
```c++
struct uri_parts {
    std::string protocol;
    std::optional<int> port;
};
uri_parts parts;
parts.has_value();
parts->protocol;
```

## 問題31 正規表現による置換



## 問題34 ファイルシステム
ファイルシステムを使いたいときは
g++ -std=c++1z -o a a.cpp -lstdc++fs
のようにオプション指定
```c++
#include<filesystem> //C++のファイルシステム
using fs = std::filesystem;
fs::path //がパスを表現するクラス
filepath.native() //で文字列を取得
auto temppath = fs::temp_directory_path() / "temp.txt"; //取得したパスのディレクトリ部分+"temp.txt";
```

## 問題35 ディレクトリ走査
指定パス以下のディレクトリを再帰的に操作するイテレータ
fs::recursive_directory_iterator
各値のクラスはfs::directory_entry

## 問題36 時間指定・ディレクトリ操作
* fs::remove()では空でないディレクトリは削除できないので、remove_allを使う
* recursive_directory_iteratorを使ってしまうと、ディレクトリを削除したときにiteratorの参照先が変更される(未定義な動作)　これを防ぐため、普通のdirectory_iteratorを使い、関数を再帰適用する
* 時間の単位はtypename Durationでテンプレート化すると良い
* std::chrono_literals をusingすると1hなどのリテラルが使える
* time_since_epoch()を足し引きして時間を計算、それをch::duration_cast<Duration>すると二点間の時間経過が計算できる

## 問題37 ロガー
* 一意な名前の作成・管理にはboost::uuidなどのライブラリが良い

## 問題39 関数の実行時間測定
* 引数として関数と引数を取り、その引数で関数を実行する方法
* テンプレートでデフォルトの時間単位を設定しつつ、関数の実行時間を測定する関数
* 細かい時間を測定したいときはch::high_resolution_clock型を用いる ２つのauto high_resolution_clock::now()の間で差分を取るなど
```c++
template <typename Time = std::chrono::microseconds,
          typename Clock = std::chrono::high_resolution_clock>
struct perf_timer 
{
    template <typename F, typename... Args> 
    static Time duration(F&& f, Args... args)
    {
        auto start = Clock::now();
        std::invoke(std::forward<F>(f), std::forward<Args>(args)...);
        auto end = Clock::now();

        return std::chrono::duration_cast<Time>(end-start);
    }
};
```
なお、std::chrono::microsecondsなどのdurationに相当するクラスから数字を抽出したいときは.count()で得られる

## 問題40
日付間の日数算出
dateライブラリ(C++20で標準)を利用する
同じディレクトリでtz.cppをともにコンパイル、その他のヘッダはインクルードするだけ
```c++
inline int number_of_days(
    int const y1, unsigned int const m1, unsigned int const d1,
    int const y2, unsigned int const m2, unsigned int const d2
)
{
    using namespace date;
    return (sys_days{year{y1}/month{m1}/day{d1}} -
            sys_days{year{y2}/month{m2}/day{d2}}).count();
}
```

## 問題42 何番目の曜日か
1年の何週目かの計算には、dateライブラリのiso_week.hヘッダを使う
```c++
auto const dt = date::year_month_day{ year{y}, ...};
auto const tiso = iso_week::year_weeknum_weekday{ dt };
```

## 問題44 カレンダーの出力
* 特定の日にちの曜日を求める
```c++
auto const dt = year_month_day{ year{y}, month{m}, day{1} };
unsigned int wn = static_cast<unsigned int>(iso_week::year_weeknum_weekday{dt}.weekday());
```
* ある年/月の日数を求める
year_month_day_last構造体を使う
```c++
day d = year_month_day_last{ year{y}, month_day_last{ month{m} } }.day();
unsigned int dl = static_cast<unsigned int>(d);
```

## 問題45 優先度付きキューの実装
* テンプレート引数に関数をとる時
```c++
template<class T, class Compare = std::less<typename std::vector<T>::value_type> >
```
のようにCompareを関数オブジェクトと定めたとき、
```c++
Compare comparer;
```
として実際の関数を定義する必要がある(Compareはただの型)
std::less<typename ...>のtypenameは、それが型の名前であるということの明示

* push_heapとpop_heapの使い方
```c++
#include<algorithm>
data.push_back(value);
std::push_heap(std::begin(data),std::end(data),comparer);

std::pop_heap(std::begin(data),std::end(data),comparer);
data.pop_back();
```

## 問題46 リングバッファの実装
* 設計：データの実際はvectorに保持するが、const_iteratorをサポートするためにイテレータの独自クラスを定義する
* デフォルトコンストラクタの禁止
```c++
class Hoge
{
    Hoge() = delete;
};
```
* フレンドクラス
```c++
class circular_buffer {
    friend class circular_buffer_iterator<T>;
};
```
で、circular_buffer_iterator<T>内から自由にcircular_buffer内にアクセスできる(非公開なメンバ変数+メンバ関数)

* C++でのポインタの取得
参照からポインタを得たいときはstd::addressof(参照)とする

* 前置/後置インクリメントそれぞれの定義
```c++
self_type & operator++() //前置
self_type operator++(int) //後置
```

* T& a と T& b の中身でなく参照そのもの(同一のオブジェクトを指してるか)を比較したいとき
```c++
return &a == &b;
```

* イテレータの定義サンプル
そのまま載せておく
```c++
template<class T>
class circular_buffer_iterator
{
    //型名の被覆
    using self_type         = circular_buffer_iterator;
    using value_type        = T;
    using reference         = T&;
    using const_reference   = T const&;
    using pointer           = T*;
    using const_pointer     = T const*;
    using iterator_category = std::random_access_iterator_tag;
    using difference_type   = ptrdiff_t;

private:    
    circular_buffer<T> const & buffer_; //リングバッファ本体の参照
    size_t index_; //インデックス
    bool last_; //最後の要素かのフラッグ

    bool compatible(self_type const& other) const
    {
        return &buffer_ == &other.buffer_;
    }

public:
    circular_buffer_iterator(circular_buffer<T> const & buf, 
        size_t const pos, bool const last)
        : buffer_(buf), index_(pos), last_(last) {}
    
    self_type & operator++()
    {
        if (last_)
            throw std::out_of_range("Iterator cannot be incremented.");
        index_ = (index_ + 1) % buffer_.data_.size();
        last_ = index_ == buffer_.next_pos();
        return *this;
    }

    self_type operator++(int)
    {
        self_type itr = *this;
        ++(*this);
        return itr;
    }

    bool operator==(self_type const & other) const 
    {
        assert(compatible(other));
        return (index_ == other.index_) && (last_ == other.last_);
    }

    bool operator!=(self_type const & other) const 
    {
        return !(*this == other);
    }

    const_reference operator*() const
    {
        return buffer_.data_[index_];
    }

    const_pointer operator->() const 
    {
        return std::addressof(operator*());
    }
};
```

## 問題47 ダブルバッファ mutex管理
* constメンバ関数内でも変更できる変数の指定方法
```c++
mutable std::mutex mtx;
```
* コンテナへの書き込みはstd::copyを使おう
* std::threadの機能を使っているときはコンパイルオプションに-pthreadを
* 新たなスレッドの生成と実行
```c++
int x = 0;
std::thread t([&x]() {
    for (int i = 1; i < 1000; i+=10) x++;
});
t.join();
```

## 問題48 配列内最多出現要素の列挙
* std::max_element()を使えば出現回数最大の要素が求まる　結果の型は連想配列mapの要素であり、要素と出現回数のペア
ただしmax_elementの返り値はイテレータ
* std::copy_if()で特定の関数を指定すれば条件を満たす要素のみコピーできる

## 問題49 文字列のアルファベット出現頻度ヒストグラム化
* 自分の解答ではgnuplotへ標準出力をパイプした
    * コマンドライン引数でファイル名、文字列を指定する（都合上ファイル名が先、残り全てを結合する）
    * gnuplotの都合上、データは分離していったんtmp.dataに出力する これにuuidを使えるとさらに危険が減る
    * WSLの都合上出力は直接表示はできず、png出力のみに絞った

## 問題50 電話番号フィルタリング
* vector全体に操作する関数を作るときに必ず適用するデザインパターンとして、イテレータの開始位置、終了位置を指定するテンプレート関数を書いた後に本命のvectorへの操作の同名関数を書く
* back_inserter(vector)の使い道：std::copyやcopy_ifなどでのコピー先のベクトル用のイテレータとして使う　自動的にコピーした分だけ長さが調節される
* 部分文字列発見にはstr.find(prefix)がよい　見つけたインデックスが返る

## 問題51 電話番号に国際番号付加
* std::transform(vec.cbegin(),vec.cend(),vec.begin(),func)でvecを変形する
* 文字列から空白を除く
```c++
str.erase(
    std::remove_if(str.begin(),str.end(),
    [](const char c) {return isspace(c)};),
str.end);
```

## 問題53 映画レビューの平均
* 小数点以下n桁の出力に固定する
```c++
std::cout << std::fixed << std::setprecision(n)
```
* 映画レビューのvectorに操作を行う関数と、トリム平均を求める関数は全く別の役割なので関数を分ける

## 問題55 ZIPアルゴリズム
* イテレータ引数版テンプレートの上にvector版のレイヤを重ねる イテレータ版は返り値のコンテナを作れないため出力用引数としてback_inserterを取ることにする
```c++
template<typename I1, typename I2, typename Output>
void zip(I1 const begin1, I1 const end1,
         I2 const begin2, I2 const end2, Output result)
{
    I1 it1 = begin1;
    I2 it2 = begin2;
    while (it1 != end1 && it2 != end2)
    {
        result++ = std::make_pair(*it1++,*it2++);
    }
}

template<typename T, typename U>
std::vector<std::pair<T, U> > zip(std::vector<T> const& a,
                             std::vector<U> const& b)
{
    std::vector<std::pair<T,U> > result;
    zip(a.cbegin(),a.cend(),b.cbegin(),b.cend(),std::back_inserter(result));
    return result;
}
```

## 問題56 テンプレート内で関数の返り値の型を求める
* vector<T,A>を引数にとる関数Fの返り値を求めた型がR(注意)result_ofはC++20で削除、代わりにinvoke_resultを利用する
```c++
template <
typename T, typename A, typename F,
typename R = typename std::decay<typename std::result_of<
             typename std::decay<F>::type&(
             typename std::vector<T,A>::const_reference)>::type>::type>
std::vector<R> select(std::vector<T,A> const& c, F&& f)
{
    std::vector<R> v;
    std::transform(c.begin(),c.end(),std::back_inserter(v),
                   std::forward<F>(f));
    return v;
}
```
* invoke_resultの使用例
```c++
template<typename T, typename F>
typename std::invoke_result<F, T const&>::type myselect(T const& a, F&& f)
{
    return f(a);
    //return std::forward<F>(f)(a);
}
```
関数Fとconst参照Tをとって関数を適用した結果を返す場合

## 問題57 テンプレート版クイックソート
* イテレータの指す値の型を求める時
```c++
std::iterator_traits<Iterator>::value_type
```
* イテレータが指す値同士を交換するとき
```c++
std::iter_swap(itr1, itr2);
```

## 問題58 グラフアルゴリズム
頂点型、重みをテンプレート化して隣接リストをmapで実現し、ダイクストラ法で最短距離を求めるのが本での解答

## 問題60 ライフゲーム
* 初期化の内容を指定したオプションで変更したいとき、クラス定義内にenum classでオプションを表現する型を置いておき、
```c++
class Hoge
{
    enum class seed { random, all_dead, ten_cell_row };
    void initialize(seed const s )
    {
        if (s == seed::random) //...
    }
};
```
のように書くとよい

## 問題61 並行処理
* ランダムアクセスイテレータが二つ与えられたときstd::distance(begin,end)で距離が求まる
* std::vector::emplace_back()
push_backと違って引数オブジェクトを直接構築して末尾に追加する
* 並行処理の数値実験結果
    * 並行処理化の配列サイズしきい値が10000のとき
    配列サイズが1000, 10000, 100000, 1000000, 10000000に対し
    77μs, 500μs,|4000μs, 50000μs, 300000μs
    しきい値が100000のとき
    79μs, 500μs, 5000μs,|35000μs, 300000μs
    しきい値が1000000のとき
    79μs, 500μs, 5000μs, 70000μs,|300000μs

## 問題62 並行処理2
* std::thread t([](){ hoge });でスレッド生成
* t.join()で実行待ち

## 問題63 非同期関数
* std::async(std::launch::async, func)でfuncを非同期実行するfutureオブジェクトを生成する
* 生成したfutureオブジェクトにget()を適用することで関数の返り値を得る
```c++
{
  auto futuref = std::async(std::launch::async, []{ f(); });
  auto futureg = std::async(std::launch::async, []{ g(); });
}
futuref.get();
futureg.get();
```

## 問題64 クイックソート並列版
* 自分の解答では、区間の分割をスレッド数を超えない限り行った後残りのソートを並列にスレッドで実行した
* 本の解答では、再帰の各段階で左区間、右区間のそれぞれが一定サイズ以上なら非同期関数を生成して並列に実行した
* 実験結果(しきい値10000)
    * 山形データ サイズ1000000 非並列版 2727ms  
    * 山形データ サイズ1000000 並列版 1168ms
    * 降順データ サイズ20000 非並列版 5082ms  
    * 降順データ サイズ20000 並列版 5093ms

## 問題65 スレッドセーフなロガー
* 自分の解答は
```c++
class Logger 
{
private:    
    std::mutex mx;
public:
    Logger() : {}
    void log(string cosnt& s)
    {
        std::lock_guard<std::mutex> lock(mx);
        std::cout << s << std::endl;
    }
};
```
だったが、これだと問題(インスタンスごとにミューテックスが異なるため)
* オブジェクトが唯一しか存在しないようにすればよい
* スレッド安全なSingleton(シングルトン)として実装する
* 静的メソッドinstance()はローカルな静的オブジェクトへの参照を返す


## 問題67 デザインパターン・パスワード検証
* 自分の回答では可変長引数として関数を取ってパスワード検証するテンプレートを書いたn
* 本の解答ではデコレータパターンを使っていた
* 検証のパターンごとにデコレータクラスを継承して新たな検証用クラスを作る　検証用クラスの種類で上層のクラス実装が影響されない
* 最上層のpassword_validatorは抽象クラスとして純粋仮想関数で実装する
* 次の層のpassword_validator_decoratorはvalidatorを継承し、別のvalidatorのポインタを保持してチェーンを形成する
* validate関数をオーバーライドして全てのandを返す

## 問題69 デザインパターン・社会保障番号生成
* protectedメンバはprivateとpublicの中間(継承したクラスでのみアクセスできるメンバ)
* southeriaとnoutheriaの違いは性別・乱数の桁数・チェックサムの法のみ これらをメンバ関数として実装した一般のクラスSocial_number_generatorを実装する
* それを継承した各子クラスでメンバ関数の実体をオーバーライドして作成する
* Social_number_generatorの各派生を分かりやすくインスタンス化するためラッパークラス_factoryを実装する(継承はしない)
* std::unique_ptrにget()を適用すると元のポインタを得る

## 問題70 デザインパターン・従業員購入の承認
* 抽象クラスRoleを継承して各役職に承認リミットを設定
* employeeクラスはRoleと名前を実体に持つ連結リストとする
* approve関数は連結リスト上のたらいまわしにする 

## 問題71 デザインパターン・観察可能なベクトルコンテナ
* observable_vectorでvectorをラップして必要な操作を備え、collection_observerへのポインタリストを保持する
* observable_vectorの内部状態で何か変化が起こると、登録されたobserverたちのcollection_changed()メソッドが呼び出される

## 問題72 デザインパターン・割引システム(ストラテジパターン)
* 割引を表現するクラスを継承で作成、オーダーごと、商品1まとめごと、商品1種類ごとのそれぞれに対し割引クラスのポインタを保持させる
* 別のクラスprice_calculatorでこれらの割引クラスを用いて計算するアルゴリズムを実装する(引数にorderクラスを取る)

## 問題73 XML解析
* BoostのXMLパーサが使える
```c++
boost::property_tree::ptree pt;
read_xml(filename, pt);
```
でptreeに読み込んだXMLを取得
* が、外部のライブラリを使ったほうが効果的らしい
* tinyxml2を利用した
    * ヘッダtinyxml2.hをインクルード、tinyxml2.cppをコンパイルするだけでよし 名前空間tinyxml2に注意

## 問題74 XPath
* XPathによる属性などの効率的な指定
* tinyxml2がサポートしていなかったためスルー

## 問題75 JSONシリアライズ
* json.hppを使った
    * ヘッダオンリーのライブラリ

## 問題76 JSONデシリアライズ

## 問題77
## 問題78
* PDF-Writer(Hummus) ライブラリを使用 利用法がよくわからないのでいったんスルー


## 問題82 PNG作成
* PNGWriterを利用
    * コンパイルオプションg++-8 -o pr82 pr82.cpp -std=c++17 -I/usr/include/freetype2 -L/usr/local/lib -lz -lPNGwriter -lpng -lfreetype
* ルーマニア国旗の作成
```c++
#include<pngwriter.h>
int main(){
    pngwriter png(450,300,0,"test.png");
    png.filledsquare(0,0,150,300,0,0,65535);
    png.filledsquare(151,0,300,300,65535,65535,0);
    png.filledsquare(301,0,450,300,65535,0,0);
    png.close();
}
```

## 問題85 SQLiteデータベース
* gccではsqlite3.hヘッダファイルで連携可能
* コンパイルオプション-lsqlite3
* 自分の回答ではhttps://tociyuki.hatenablog.jp/entry/20141218/1418914334のsqlite3C++ラッパーを利用させて頂いた
* 本ではsqlite_modern_cppライブラリを利用していた(sqlite_modern_cpp.hをインクルードするのみで使用可能)
    * sqlite::databaseクラスは演算子<<と>>を持つ
        * <<で命令文を入力する 文内に?を入れておけばその後の<<で?にパラメータ入力可能
        * \>>で引数としてデータを取って処理を実行するラムダ式に入力する  

## 問題86 SQLiteデータベースにトランザクション挿入
* 空白を含む文字列の入力にはgetlineを使う
    * 自作splitも活用
* BEGIN命令でトランザクションを開始、COMMIT命令で完了する 完了前にエラーが発生するとBEGIN以降の変更は反映されない

## 問題87 SQLiteデータベースにメディアファイルのバイナリ追加
* バイナリデータの扱い方
    * ファイルから取り込み
    ```c++
    std::vector<char> data;
    std::ifstream ifile(filepath, std::ios::binary  std::ios::ate); //入力ストリームを終端から開始
    if (ifile.is_open())
    {
        auto size = ifile.tellg(); //ファイルサイズ
        ifile.seekg(0, std::ios::beg); //ストリームを最初に戻す

        data.resize(static_cast<size_t>(size)); //バッファサイズを合わせる
        ifile.read(data.data(),size); //vector<char>に読む
    }
    return data;
    ```

## 問題88 シーザー暗号
* 各文字の一定距離シフトによる単純な暗号

## 問題89 ヴィジュネル暗号
* 平文と鍵と表を利用して暗号化

## 問題90 BASE64
* base64暗号:バイナリ符号化法　6ビットずつ取ってきてそれぞれ対応する文字に変換する
* coutに二進数出力する方法
```c++
std::cout << std::bitset<width>(i);
```
* バイナリデータを管理する際はunsigned charを1単位にするとよい unsigned charは8ビット(1バイト)

## 問題91 SHA暗号
* Crypto++ライブラリを使用 コンパイルオプション-lcrypto++
* CryptoPP::byteは存在しない 代わりにグローバル名前空間のbyteを使う

## 問題92 ファイルハッシュの計算

## 問題93 ファイルの暗号化

## 問題94 ファイルの署名検証


## 問題95 
* スタンドアロンASIOライブラリ
```c++
#define ASIO_STANDALONE 
#include "asio/include/asio.hpp"
```
* コンパイル時は-lpthreadが必要

## 問題96 クライアント-サーバfizzbuzz
* サーバ側：指定されたポートのTCPコネクションをアクセプトし、接続されたソケットを開き、ソケットの読み込みを開始する。ソケットから何か読むと、応答を返し次の入力を待つ。asio::ip::tcp::socketのメンバasync_read_someとasync_write_someは非同期関数で、第一引数のバッファに読み書きを実行したのち第二引数のハンドラを呼び出す。
    * acceptメンバ
    ```c++
    void accept()
    {
        tcp_acceptor.async_accept(tcp_socket,[this](std::error_code ec)
            {
                if (!ec)
                    std::make_shared<session>(std::move(tcp_socket))->start();
                accept();
            }
        );
    }
    ```
    * readメンバ
    ```c++
    void read()
    {
        auto self(shared_from_this());
        tcp_socket.async_read_some(
            asio::buffer(data, data.size()),
            [this,self](std::error_code const ec, size_t const length){
                if (!ec)
                {
                    auto number = std::string(data.data(),length);
                    auto result = fizzbuzz(std::atoi(number.c_str()));
                    std::cout << number << "->" << result << std::endl;
                    write(result);
                }
            }
        );
    }
    ```
    * writeメンバ
    ```c++
    void write(std::string_view response)
    {
        auto self(shared_from_this());
        tcp_socket.async_write_some(
            asio::buffer(response.data(),response.length()),
            [this,self](std::error_code const ec, size_t const) {
                if (!ec) read();
            }
        );
    }
    ```

* クライアント側：ホストの指定されたポートに接続し、送受信を無限ループする
```c++
while (true)
{
    std::cout << "number [1-99]: " ;
    int number;
    std::cin >> number;
    if (std::cin.fail() || number < 1 || number > 99)
        break;
    
    auto request = std::to_string(number);
    tcp_socket.write_some(asio::buffer(request,request.size()));

    std::array<char,1024> reply;
    auto reply_length = tcp_socket.read_some(
        asio::buffer(reply,reply.size())
    );

    std::cout << "reply is: ";
    std::cout.write(reply.data(), reply_length);
    std::cout << std::endl;
}
```
* shared_ptrを自作クラスTで使いたいときstd::enable_shared_from_this<T>を継承する
    * このときshared_from_this()でthisに相当するポインタオブジェクトを取得

## 問題97 HTTPS GET
* libcurlとcurlpp(C++ラッパー)を用いる

## 問題99 翻訳WEBサービスの利用
* google翻訳をGAS(google apps script)で利用した
* google_translate_apiなるサービスを実装
```javascript
//main.gsファイル
function doGet(e) {
    var p = e.parameter;
    var translatedText = LanguageApp.translate(p.text, p.source, p.target);
    var body;
    if (translatedText) {
        body = {
          code: 200,
          text: translatedText
        };
    } else {
        body = {
          code: 400,
          text: "Bad Request"
        };
    }
    var response = ContentService.createTextOutput();
    response.setMimeType(ContentService.MimeType.JSON);
    response.setContent(JSON.stringify(body));
    return response;
}
```
* URLを公開して、curlppでパラメータを指定したうえでhttp getを実行
    * GASではセキュリティ上の理由からレスポンスのURLがリダイレクトされる
        * req.setOpt(new FollowLocation(1L));でリダイレクト可能になる

## 問題100 画像内にある顔を検出する
* opencvを利用(cascadeclassifier)顔認識に必要なxmlファイルはopencv-masterに付属したもの
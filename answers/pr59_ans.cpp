/*
1.はじめに28文字のランダムな文字列を設定する
2.コピーを100個作り、5%の確率でランダムな文字に入れ替わるようにする
3.入れ替えた文字列を見本と比較して、同じ文字が同じ位置にいる数をスコアとする
4.入れ替えた文字列のいずれかが満点を取ったら停止
5.満点がない場合、最高点を取った文字列で2に戻る
*/

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

class Weasel
{
    std::string target;
    std::uniform_int_distribution<> chardist;
    std::uniform_real_distribution<> ratedist;
    std::mt19937 mt;
    std::string const allowed_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ ";

public:
    explicit Weasel(std::string const& t) : 
    target(t), chardist(0,26), ratedist(0,100)
    {
        std::random_device rd;
        auto seed_data = std::array<int, std::mt19937::state_size> {};
        std::generate(seed_data.begin(),seed_data.end(),std::ref(rd));
        std::seed_seq seq(seed_data.cbegin(),seed_data.cend());
        mt.seed(seq);
    }

    void run(int const copies = 100)
    {
        auto parent = make_random();
        int step = 1;
        std::cout << std::left << std::setw(5) << std::setfill(' ') << step 
                  << parent << std::endl;

        do 
        {
            std::vector<std::string> children;
            std::generate_n(std::back_inserter(children),
                            copies, 
                            [parent, this](){ return mutate(parent,5); });
            parent = *std::max_element(
                std::cbegin(children), std::cend(children),
                [this](std::string c1, std::string c2)
                { return fitness(c1) < fitness(c2); }
            );
            std::cout << std::setw(5) << std::setfill(' ')
                      << step << parent << std::endl;
            step++;
        } while (parent != target);
    }

    Weasel() = delete;

    int fitness(std::string const& candidate)
    {
        int score = 0;
        for (size_t i = 0; i < candidate.size(); i++)
        {
            if (candidate[i] == target[i])
            {
                score++;
            }
        }

        return score;
    }

    std::string mutate(std::string const& parent, double const rate)
    {
        std::stringstream sstr;
        for (auto const c : parent)
        {
            auto nc = ratedist(mt) > rate ? c : allowed_chars[chardist(mt)];
            sstr << nc;
        }
        return sstr.str();
    }

    std::string make_random()
    {
        std::stringstream sstr;
        for (size_t i = 0; i < target.size(); i++)
        {
            sstr << allowed_chars[chardist(mt)];
        }
        return sstr.str();
    }
};


int main()
{
    Weasel w("METHINKS IT IS LIKE A WEASEL");
    w.run();
}
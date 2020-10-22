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


class Universe
{
    enum class State { dead, alive };
private:
    size_t row;
    size_t col;
    std::vector<std::vector<State>> grid;
    std::vector<std::vector<State>> buffer_grid;

    std::uniform_real_distribution<> ratedist;
    std::mt19937 mt;
public:
    explicit Universe(size_t const r, size_t const c)
    : row(r), col(c), ratedist(0,100), 
      grid(r, std::vector<State>(c,State::dead)),
      buffer_grid(r, std::vector<State>(c,State::dead)) 
    {
        std::random_device rd;
        auto seed_data = std::array<int, std::mt19937::state_size> {};
        std::generate(seed_data.begin(),seed_data.end(),std::ref(rd));
        std::seed_seq seq(seed_data.cbegin(),seed_data.cend());
        mt.seed(seq);
    }

    Universe() = delete;

    void initialize()
    {
        for (size_t i = 0; i < row; i++)
            std::fill(grid[i].begin(),grid[i].end(),State::dead);
    }

    void randomize(int const rate = 10)
    {
        for (size_t i = 0; i < row; i++)
        {
            for (size_t j = 0; j < col; j++)
            {
                grid[i][j] = (ratedist(mt) < rate)
                ? State::alive : State::dead;
            }
        }
    }

    State next_state(size_t const i, size_t const j)
    {
        if (i < 0 || i >= row || j < 0 || j >= col) throw std::invalid_argument("out of grid");
        int cnt = 0;
        for (auto [x, y] : std::vector<std::pair<size_t,size_t>>
        {std::make_pair(i-1,j), std::make_pair(i+1,j),
         std::make_pair(i,j+1), std::make_pair(i,j-1)})
        {
            if (x >= 0 && x < row && y >= 0 && y < col)
            {
                if (grid[x][y] == State::alive) cnt++;
            }
        }
        if (grid[i][j] == State::alive)
        {
            if (cnt == 2 || cnt == 3) return State::alive;
            else return State::dead;
        } 
        else 
        {
            if (cnt == 3) return State::alive;
            else return State::dead;
        }
    }

    void next_generation()
    {
        for (size_t i = 0; i < row; i++)
        {
            for (size_t j = 0; j < col; j++)
            {
                buffer_grid[i][j] = next_state(i,j);
            }
        }
        swap(grid,buffer_grid);
    }

    void print_grid() const
    {
        for (size_t i = 0; i < row; i++)
        {
            for (size_t j = 0; j < col; j++)
            {
                if (grid[i][j] == State::alive) std::cout << 'X';
                else std::cout << ' ';
            }
            std::cout << std::endl;
        }
    }

    void run(int const steps = 10, int const rate = 10)
    {
        randomize(rate);
        std::cout << "Step 0: " << std::endl;
        print_grid();
        for (int i = 0; i < steps; i++)
        {
            next_generation();
            std::cout << "Step " << i+1 << ": " << std::endl;
            print_grid();

            using namespace std::chrono_literals;
            std::this_thread::sleep_for(0.5s);
        }
    }
};



int main()
{
    Universe life_game {20,50};
    life_game.run(30,40);
}
#pragma once
#include <random>
#include "grid.hpp"
#include "constants.hpp"

namespace Model
{

class Game
{
public:
    Game(IGrid& grid): m_grid(grid),
        m_rd(), m_gen(m_rd()),
        m_rowGenerator(0, m_grid.rows()),
        m_colGenerator(0, m_grid.cols())
    {}

    void init();

private:
    void rollNewBonus();

    IGrid& m_grid;

    std::random_device m_rd;
    std::mt19937 m_gen;
    std::uniform_int_distribution<size_t> m_rowGenerator;
    std::uniform_int_distribution<size_t> m_colGenerator;
};

}

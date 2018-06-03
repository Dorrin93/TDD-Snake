#include "game.hpp"

namespace Model
{

void Game::init()
{
    const size_t MIDDLE_X = m_grid.rows() / 2;
    const size_t MIDDLE_Y = m_grid.cols() / 2;

    m_grid.setPointType(MIDDLE_X, MIDDLE_Y, PointType::SNAKE);
    rollNewBonus();
}

void Game::rollNewBonus()
{
    auto row = m_rowGenerator(m_gen);
    auto col = m_colGenerator(m_gen);

    while(m_grid.getPointType(row, col) != PointType::EMPTY)
    {
        row = m_rowGenerator(m_gen);
        col = m_colGenerator(m_gen);
    }

    m_grid.setPointType(row, col, PointType::BONUS);
}

}


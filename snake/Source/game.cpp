#include "game.hpp"
#include <chrono>
#include <iostream>

namespace Model
{

Game::Game(IGrid &grid, ISnake &snake):
    m_grid(grid), m_snake(snake),
    m_rowGenerator(0, m_grid.rows()-1),
    m_colGenerator(0, m_grid.cols()-1)
{
}

void Game::init()
{
    const auto& head = m_snake.head();
    m_grid.setPointType(head.x, head.y, PointType::SNAKE);
    m_headNow = head;
    rollNewBonus();
}

bool Game::nextStep()
{
    m_tailBefore = m_snake.tail();
    m_headNow = m_snake.move(m_bonus);

    if(m_headNow.x >= m_grid.cols() or m_headNow.x < 0 or
       m_headNow.y >= m_grid.rows() or m_headNow.y < 0 or
       m_grid.getPointType(m_headNow.x, m_headNow.y) == PointType::SNAKE)
    {
        return false;
    }

    m_grid.setPointType(m_headNow.x, m_headNow.y, PointType::SNAKE);

    if(m_headNow == m_bonus)
    {
        m_tailBefore = {-1, -1};
        rollNewBonus();
    }
    else
    {
        m_grid.setPointType(m_tailBefore.x, m_tailBefore.y, PointType::EMPTY);
    }


    return true;
}

void Game::changeDirection(Direction d)
{
    m_snake.setDirection(d);
}

void Game::rollNewBonus()
{
    auto row = m_rowGenerator(getGenerator());
    auto col = m_colGenerator(getGenerator());

    while(m_grid.getPointType(row, col) != PointType::EMPTY)
    {
        row = m_rowGenerator(getGenerator());
        col = m_colGenerator(getGenerator());
    }

    m_bonus.x = row;
    m_bonus.y = col;
}

std::mt19937& Game::getGenerator()
{
    const static auto seed =
            std::chrono::system_clock::now().time_since_epoch().count();
    static std::mt19937 generator(seed);

    return generator;
}

}


#include "game.hpp"
#include <iostream>

namespace Model
{

Game::Game(IGrid &grid, ISnake &snake,
           IPointGenrator &generator):
    m_grid(grid), m_snake(snake),
    m_generator(generator)
{}

void Game::init()
{
    m_headNow = m_snake.head();
    m_grid.setPointType(m_headNow, PointType::SNAKE);
    rollNewBonus();
}

// TODO split / refactor
bool Game::nextStep()
{
    m_snake.setDirection(m_bufferedDirection);
    m_headBefore = m_snake.head();
    m_tailBefore = m_snake.tail();
    m_headNow = m_snake.move(m_bonus);

    if(static_cast<size_t>(m_headNow.x) >= m_grid.cols() or m_headNow.x < 0 or
       static_cast<size_t>(m_headNow.y) >= m_grid.rows() or m_headNow.y < 0 or
       (m_grid.getPointType(m_headNow) == PointType::SNAKE and
        m_headNow != m_tailBefore))
    {
        return false;
    }

    m_grid.setPointType(m_headNow, PointType::SNAKE);

    if(m_headNow == m_bonus)
    {
        m_tailBefore = {-1, -1};
        rollNewBonus();
    }
    else
    {
        m_grid.setPointType(m_tailBefore, PointType::EMPTY);
    }


    return true;
}

void Game::changeDirection(Direction d)
{
    m_bufferedDirection = d;
}

void Game::reset(const Point &snakeHead)
{
    m_grid.reset();
    m_snake.reset(snakeHead);
    m_headBefore = {0, 0};
    m_tailBefore = {0, 0};
    m_bufferedDirection = Direction::RIGHT;

    init();
}

void Game::rollNewBonus()
{
    auto point = m_generator.getRandomPoint();

    while(m_grid.getPointType(point) != PointType::EMPTY)
    {
        point = m_generator.getRandomPoint();
    }

    m_bonus = point;
}

}


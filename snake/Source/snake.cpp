#include "snake.hpp"

namespace Model
{

namespace
{
Point translateDirection(Direction d)
{
    switch (d)
    {
        case Direction::DOWN:  return {0, 1};
        case Direction::UP:    return {0, -1};
        case Direction::LEFT:  return {-1, 0};
        case Direction::RIGHT: return {1, 0};
    }
    return {0, 0};
}

}

Snake::Snake(Point head):m_body({head})
{}

Point &Snake::move(const Point &bonus)
{
    enlarge();
    if(m_body.front() != bonus)
    {
        m_body.pop_back();
    }
    return m_body.front();
}

const Point& Snake::head() const
{
    return m_body.front();
}

const Point& Snake::tail() const
{
    return m_body.back();
}

Direction Snake::direction() const
{
    return m_direction;
}

void Snake::setDirection(Direction d)
{
    if(isOposite(d) and m_body.size() > 1)
    {
        return;
    }
    m_direction = d;
}

size_t Snake::size() const
{
    return m_body.size();
}

void Snake::enlarge()
{
    const auto& head = m_body.front();
    const auto shift = translateDirection(m_direction);
    m_body.emplace_front(head + shift);
}

bool Snake::isOposite(Direction d)
{
    return (m_direction == Direction::LEFT and d == Direction::RIGHT) or
           (m_direction == Direction::RIGHT and d == Direction::LEFT) or
           (m_direction == Direction::UP and d == Direction::DOWN) or
            (m_direction == Direction::DOWN and d == Direction::UP);
}

}

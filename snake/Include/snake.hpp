#pragma once
#include <deque>
#include <cstddef>
#include "point.hpp"

namespace Model
{

enum class Direction { LEFT, RIGHT, UP, DOWN };

class ISnake
{
public:
    virtual ~ISnake(){}

    virtual Point& move(const Point&) = 0;

    virtual const Point& head() const = 0;
    virtual const Point& tail() const = 0;

    virtual Direction direction() const = 0;
    virtual void setDirection(Direction) = 0;

    virtual size_t size() const = 0;

    virtual void reset(const Point&) = 0;
};

class Snake: public ISnake
{
public:
    Snake(Point head);

    Point& move(const Point& bonus) override;

    const Point& head() const override;
    const Point& tail() const override;

    Direction direction() const override;
    void setDirection(Direction d) override;

    size_t size() const override;

    void reset(const Point& head) override;

private:
    void enlarge();
    bool isOposite(Direction d);

    Direction m_direction = Direction::RIGHT;
    std::deque<Point> m_body;
};

}

#pragma once
#include "grid.hpp"
#include "snake.hpp"
#include "pointgenerator.hpp"
#include "point.hpp"

namespace Model
{

class Game
{
public:
    explicit Game(IGrid& grid, ISnake& snake,
                  IPointGenrator &generator);

    void init();
    bool nextStep();
    void changeDirection(Direction d);
    Direction getDirection() const { return m_snake.direction(); }

    size_t getSnakeSize() const { return m_snake.size(); }

    const Point& getBonusPlacement()      const { return m_bonus; }
    const Point& getHeadNowPlacement()    const { return m_headNow; }
    const Point& getTailBeforePlacement() const { return m_tailBefore; }
    const Point& getHeadBeforePlacement() const { return m_headBefore; }

    void reset();

private:
    void rollNewBonus();

    IGrid& m_grid;
    ISnake& m_snake;
    IPointGenrator& m_generator;
    Point m_bonus{0, 0};
    Point m_headNow{0, 0};
    Point m_headBefore{0, 0};
    Point m_tailBefore{0, 0};
    Direction m_bufferedDirection = Direction::RIGHT;
};

}

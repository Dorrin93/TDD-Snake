#pragma once
#include <random>
#include "grid.hpp"
#include "snake.hpp"
#include "point.hpp"

namespace Model
{

class Game
{
public:
    explicit Game(IGrid& grid, ISnake& snake);

    void init();
    bool nextStep();
    void changeDirection(Direction d);

    const Point& getBonusPlacement()      const { return m_bonus; }
    const Point& getHeadNowPlacement()    const { return m_headNow; }
    const Point& getTailBeforePlacement() const { return m_tailBefore; }

    // ONLY FOR TESTING PURPOSE //
    // TODO resolve by creating and
    //  mocking random generator
    void setBonusPlacement(int x, int y)
    {
        m_bonus.x = x;
        m_bonus.y = y;
    }
    // ONLY FOR TESTING PURPOSE //

private:
    static std::mt19937& getGenerator();
    void rollNewBonus();

    IGrid& m_grid;
    ISnake& m_snake;
    Point m_bonus{0, 0};
    Point m_headNow{0, 0};
    Point m_tailBefore{0, 0};

    std::uniform_int_distribution<size_t> m_rowGenerator;
    std::uniform_int_distribution<size_t> m_colGenerator;
};

}

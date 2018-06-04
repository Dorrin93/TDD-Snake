#include "gamecontroller.hpp"
#include <iostream>

namespace Controller
{

void GameController::start()
{
    m_game.init();
    connect(&m_timer, SIGNAL(timeout()), this, SLOT(update()));
    m_timer.start(GameContants::TIMEOUT);
}

void GameController::changeDirection(Model::Direction d)
{
    m_game.changeDirection(d);
}

void GameController::update()
{
    bool result = m_game.nextStep();
    if(!result)
    {
        m_timer.stop();
        std::cout << "END" << std::endl;
        return;
    }
    const auto point = m_game.getHeadNowPlacement();
    std::cout << point.x << " " << point.y << std::endl;

    emit updateDone();
}

}

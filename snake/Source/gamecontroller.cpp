#include "gamecontroller.hpp"
#include <iostream>

namespace Controller
{

using namespace std::chrono;

void GameController::start()
{
    m_game.init();
    connect(&m_timer, SIGNAL(timeout()), this, SLOT(update()));
    m_timer.start(GameContants::TIMEOUT);
    m_startTime = steady_clock::now();
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
        emit gameEnd(duration_cast<seconds>(steady_clock::now() - m_startTime),
                     m_game.getSnakeSize() - 1);
        return;
    }

    emit updateDone();
}

}

#include "gamecontroller.hpp"
#include <iostream>

namespace Controller
{

using namespace std::chrono;

GameController::GameController(Model::Game &game, QObject *parent):
    QObject(parent),
    m_game(game)
{
    connect(&m_timer, SIGNAL(timeout()), this, SLOT(update()));
}

void GameController::start()
{
    m_game.init();
    m_timer.start(GameContants::TIMEOUT);
    m_startTime = steady_clock::now();
}

void GameController::restart()
{
    m_game.reset({GameContants::COLS/2, GameContants::ROWS/2});
    start();
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

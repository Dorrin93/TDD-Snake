#pragma once
#include <QObject>
#include <QTimer>
#include <chrono>
#include "constants.hpp"
#include "grid.hpp"
#include "game.hpp"

namespace Controller
{

class GameController : public QObject
{
    Q_OBJECT
public:
    GameController(Model::Game& game, QObject* parent = nullptr);

    void start();

public slots:
    void restart();
    void changeDirection(Model::Direction);
    void update();

signals:
    void updateDone();
    void gameEnd(std::chrono::seconds, size_t);

private:
    QTimer m_timer;
    Model::Game& m_game;

    std::chrono::steady_clock::time_point m_startTime;
};

}

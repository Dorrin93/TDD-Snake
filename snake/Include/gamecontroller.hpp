#pragma once
#include <QObject>
#include <QTimer>
#include "constants.hpp"
#include "grid.hpp"
#include "game.hpp"

namespace Controller
{

class GameController : public QObject
{
    Q_OBJECT
public:
    GameController(Model::Game& game, QObject* parent = nullptr):
        QObject(parent),
        m_game(game)
    {}

    void start();
public slots:
    void changeDirection(Model::Direction);
    void update();

signals:
    void updateDone();
    void gameEnd();

private:
    QTimer m_timer;
    Model::Game& m_game;
};

}

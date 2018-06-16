#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include "constants.hpp"
#include <QKeyEvent>
#include <chrono>
#include "snake.hpp"
#include "scoreboard.hpp"

namespace Ui
{
class MainWindow;
}

namespace Model
{
class Game;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(const Model::Game& game, QWidget *parent = 0);
    ~MainWindow();

public slots:
    void redraw();
    void endGame(std::chrono::seconds, size_t);

signals:
    void directionChanged(Model::Direction);
    void restartChosen();

private:
    void prepareScene();
    void drawHead(const Model::Point&);
    void drawGrid();
    void drawWalls();
    void keyPressEvent(QKeyEvent* event);

    Ui::MainWindow *ui;
    QGraphicsScene m_scene;
    ScoreBoard m_scores;
    const Model::Game& m_game;

    static const qreal delta;
    static const qreal size;
};

#endif // MAINWINDOW_H

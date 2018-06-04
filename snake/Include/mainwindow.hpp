#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include "constants.hpp"
#include <QKeyEvent>
#include "snake.hpp"

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
    explicit MainWindow(Model::Game& game, QWidget *parent = 0);
    ~MainWindow();

public slots:
    void redraw();

signals:
    void directionChanged(Model::Direction);

private:
    void drawGrid();
    void keyPressEvent(QKeyEvent* event);

    Ui::MainWindow *ui;
    QGraphicsScene m_scene;
    Model::Game& m_game;


};

#endif // MAINWINDOW_H

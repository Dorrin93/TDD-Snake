#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include "game.hpp"
#include <iostream>
#include <qdebug.h>

using namespace GameContants;

MainWindow::MainWindow(Model::Game& game, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_game(game)
{
    ui->setupUi(this);
    ui->graphicsView->setScene(&m_scene);
    this->setFocus();

    constexpr unsigned MAIN_WINDOW_OFFSET = 50;

    this->setFixedSize(FULL_ROW_SIZE + MAIN_WINDOW_OFFSET,
                       FULL_COLS_SIZE + MAIN_WINDOW_OFFSET);

    ui->graphicsView->setFixedSize(FULL_ROW_SIZE,
                                   FULL_COLS_SIZE);

    if(GameContants::DRAW_GRID)
    {
        drawGrid();
    }

    redraw();
}

MainWindow::~MainWindow()
{
    delete ui;
}

// TODO Split and refactor
void MainWindow::redraw()
{
    const qreal delta = FIELD_SIZE / 5.;
    const qreal size = FIELD_SIZE - delta;
    const auto bonus = m_game.getBonusPlacement();

    m_scene.addEllipse(FIELD_SIZE*bonus.x + delta/2, FIELD_SIZE*bonus.y + delta/2,
                       size, size, QPen(Qt::black), QBrush(Qt::green));

    const auto head = m_game.getHeadNowPlacement();

    m_scene.addEllipse(FIELD_SIZE*head.x + delta/2, FIELD_SIZE*head.y + delta/2,
                       size, size, QPen(Qt::black), QBrush(Qt::blue));

    const auto tailBefore = m_game.getTailBeforePlacement();

    if(tailBefore.x != -1)
    {
        m_scene.addRect(FIELD_SIZE*tailBefore.x + delta/2, FIELD_SIZE*tailBefore.y + delta/2,
                        size, size, QPen(Qt::white), QBrush(Qt::white));
    }
}

void MainWindow::drawGrid()
{
    for(unsigned x = FIELD_SIZE; x < FULL_ROW_SIZE; x += FIELD_SIZE)
    {
        m_scene.addLine(x, 2, x, FULL_ROW_SIZE-2, QPen(Qt::black));
    }

    for(unsigned y = FIELD_SIZE; y < FULL_COLS_SIZE; y += FIELD_SIZE)
    {
        m_scene.addLine(2, y, FULL_COLS_SIZE-2, y, QPen(Qt::black));
    }
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
    if(event->key() == Qt::Key_Left)
    {
        emit directionChanged(Model::Direction::LEFT);
    }
    if(event->key() == Qt::Key_Right)
    {
        emit directionChanged(Model::Direction::RIGHT);
    }
    if(event->key() == Qt::Key_Up)
    {
        emit directionChanged(Model::Direction::UP);
    }
    if(event->key() == Qt::Key_Down)
    {
        emit directionChanged(Model::Direction::DOWN);
    }
    if(event->key() == Qt::Key_Escape)
    {
        QApplication::quit();
    }

}

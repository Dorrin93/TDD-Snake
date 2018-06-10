#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include "game.hpp"
#include <iostream>
#include <qdebug.h>

using namespace GameContants;

const qreal MainWindow::delta = FIELD_SIZE / 5.;
const qreal MainWindow::size = FIELD_SIZE - delta;

MainWindow::MainWindow(Model::Game& game, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_game(game)
{
    ui->setupUi(this);
    ui->graphicsView->setScene(&m_scene);
    this->setFocus();

    constexpr unsigned MAIN_WINDOW_OFFSET = 50;

    this->setFixedSize(FULL_COLS_SIZE + MAIN_WINDOW_OFFSET,
                       FULL_ROW_SIZE + MAIN_WINDOW_OFFSET);

    ui->graphicsView->setFixedSize(FULL_COLS_SIZE,
                                   FULL_ROW_SIZE);

    drawWalls();
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

void MainWindow::redraw()
{
    const auto& bonus = m_game.getBonusPlacement();

    m_scene.addEllipse(FIELD_SIZE*bonus.x + delta/2, FIELD_SIZE*bonus.y + delta/2,
                       size, size, QPen(Qt::black), QBrush(Qt::blue));

    const auto& head = m_game.getHeadNowPlacement();
    drawHead(head);

    const auto& tailBefore = m_game.getTailBeforePlacement();

    if(tailBefore.x != -1 and tailBefore != head)
    {
        m_scene.addRect(FIELD_SIZE*tailBefore.x + delta/2, FIELD_SIZE*tailBefore.y + delta/2,
                        size, size, QPen(Qt::white), QBrush(Qt::white));
    }

    const auto& headBefore = m_game.getHeadBeforePlacement();
    if(headBefore != tailBefore)
    {
        m_scene.addEllipse(FIELD_SIZE*headBefore.x + delta/2, FIELD_SIZE*headBefore.y + delta/2,
                           size, size, QPen(Qt::black), QBrush(Qt::green));
    }
}

void MainWindow::drawHead(const Model::Point& head)
{
    m_scene.addEllipse(FIELD_SIZE*head.x + delta/2, FIELD_SIZE*head.y + delta/2,
                       size, size, QPen(Qt::black), QBrush(Qt::green));
    QPointF vertex1;
    QPointF vertex2;
    QPointF vertex3;

    const auto direction = m_game.getDirection();

    const qreal insideDelta = MainWindow::delta+2;
    switch(direction)
    {
        case Model::Direction::RIGHT:
        {
            vertex1 = QPointF(FIELD_SIZE*head.x + insideDelta,
                              FIELD_SIZE*head.y + insideDelta);
            vertex2 = QPointF(FIELD_SIZE*head.x + insideDelta,
                              FIELD_SIZE*head.y + FIELD_SIZE - insideDelta);
            vertex3 = QPointF(FIELD_SIZE*head.x + FIELD_SIZE - insideDelta,
                              FIELD_SIZE*head.y + FIELD_SIZE / 2);
            break;
        }
        case Model::Direction::LEFT:
        {
            vertex1 = QPointF(FIELD_SIZE*head.x + FIELD_SIZE - insideDelta,
                              FIELD_SIZE*head.y + insideDelta);
            vertex2 = QPointF(FIELD_SIZE*head.x + FIELD_SIZE - insideDelta,
                              FIELD_SIZE*head.y + FIELD_SIZE - insideDelta);
            vertex3 = QPointF(FIELD_SIZE*head.x + insideDelta,
                              FIELD_SIZE*head.y + FIELD_SIZE / 2);
            break;
        }
        case Model::Direction::UP:
        {
            vertex1 = QPointF(FIELD_SIZE*head.x + insideDelta,
                              FIELD_SIZE*head.y + FIELD_SIZE - insideDelta);
            vertex2 = QPointF(FIELD_SIZE*head.x + FIELD_SIZE - insideDelta,
                              FIELD_SIZE*head.y + FIELD_SIZE - insideDelta);
            vertex3 = QPointF(FIELD_SIZE*head.x + FIELD_SIZE/2,
                              FIELD_SIZE*head.y + insideDelta);
            break;
        }
        case Model::Direction::DOWN:
        {
            vertex1 = QPointF(FIELD_SIZE*head.x + insideDelta,
                              FIELD_SIZE*head.y + insideDelta);
            vertex2 = QPointF(FIELD_SIZE*head.x + FIELD_SIZE - insideDelta,
                              FIELD_SIZE*head.y + insideDelta);
            vertex3 = QPointF(FIELD_SIZE*head.x + FIELD_SIZE/2,
                              FIELD_SIZE*head.y + FIELD_SIZE - insideDelta);
            break;
        }
    }

    QPolygonF triangle;
    triangle.append({vertex1, vertex2, vertex3, vertex1});
    m_scene.addPolygon(triangle, QPen(Qt::black), QBrush(Qt::blue));
}

void MainWindow::drawGrid()
{
    for(unsigned x = FIELD_SIZE; x < FULL_COLS_SIZE; x += FIELD_SIZE)
    {
        m_scene.addLine(x, 1, x, FULL_ROW_SIZE-2, QPen(Qt::black));
    }

    for(unsigned y = FIELD_SIZE; y < FULL_ROW_SIZE; y += FIELD_SIZE)
    {
        m_scene.addLine(1, y, FULL_COLS_SIZE-2, y, QPen(Qt::black));
    }
}

void MainWindow::drawWalls()
{
   m_scene.addLine(1, 1, 1, FULL_ROW_SIZE-2, QPen(Qt::black));
   m_scene.addLine(1, 1, FULL_COLS_SIZE-2, 1, QPen(Qt::black));
   m_scene.addLine(1, FULL_ROW_SIZE-2, FULL_COLS_SIZE-2,
                   FULL_ROW_SIZE-2, QPen(Qt::black));
   m_scene.addLine(FULL_COLS_SIZE-2, 1, FULL_COLS_SIZE-2,
                   FULL_ROW_SIZE-2, QPen(Qt::black));
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

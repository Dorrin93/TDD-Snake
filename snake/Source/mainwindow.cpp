#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include "game.hpp"
#include <iostream>
#include <qdebug.h>
#include <QMessageBox>
#include <QPushButton>
#include <QInputDialog>

MainWindow::MainWindow(const Model::Game &game, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_scores(this),
    m_game(game),
    m_fieldSize(GameContants::FIELD_SIZE()),
    m_delta(m_fieldSize / 5.),
    m_size(m_fieldSize - m_delta),
    m_fullRowSize(GameContants::ROWS()*m_fieldSize),
    m_fullColsSize(GameContants::COLS()*m_fieldSize)
{
    ui->setupUi(this);
    ui->graphicsView->setScene(&m_scene);
    this->setFocus();

    constexpr unsigned MAIN_WINDOW_OFFSET = 50;

    this->setFixedSize(m_fullColsSize + MAIN_WINDOW_OFFSET,
                       m_fullRowSize + MAIN_WINDOW_OFFSET);

    ui->graphicsView->setFixedSize(m_fullColsSize,
                                   m_fullRowSize);

    prepareScene();
    redraw();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::redraw()
{
    const auto& bonus = m_game.getBonusPlacement();

    m_scene.addEllipse(m_fieldSize*bonus.x + m_delta/2, m_fieldSize*bonus.y + m_delta/2,
                       m_size, m_size, QPen(Qt::black), QBrush(Qt::blue));

    const auto& head = m_game.getHeadNowPlacement();
    drawHead(head);

    const auto& tailBefore = m_game.getTailBeforePlacement();

    if(tailBefore.x != -1 and tailBefore != head)
    {
        m_scene.addRect(m_fieldSize*tailBefore.x + m_delta/2, m_fieldSize*tailBefore.y + m_delta/2,
                        m_size, m_size, QPen(Qt::white), QBrush(Qt::white));
    }

    const auto& headBefore = m_game.getHeadBeforePlacement();
    if(headBefore != tailBefore)
    {
        m_scene.addEllipse(m_fieldSize*headBefore.x + m_delta/2, m_fieldSize*headBefore.y + m_delta/2,
                           m_size, m_size, QPen(Qt::black), QBrush(Qt::green));
    }
}

void MainWindow::endGame(std::chrono::seconds sec, size_t score)
{
    QString timeNoun{" second"};
    if(sec.count() != 1)
    {
        timeNoun += "s";
    }

    QString pointNoun{" point"};
    if(score != 1)
    {
        pointNoun += "s";
    }

    QInputDialog nameInput(this, Qt::WindowSystemMenuHint |
                                 Qt::WindowTitleHint |
                                 Qt::MSWindowsFixedSizeDialogHint);
    nameInput.setWindowTitle(tr("Game Over!"));
    nameInput.setLabelText("You lasted " + QString::number(sec.count()) + timeNoun +
                           ", and collected " + QString::number(score) + pointNoun +
                           ".\nUser name:");
    nameInput.setInputMode(QInputDialog::TextInput);
    nameInput.setTextValue("Anon");
    nameInput.setCancelButtonText(tr("Quit"));
    bool nameResult = nameInput.exec();

    if(!nameResult)
    {
        QApplication::quit();
    }
    else
    {
        QString name = nameInput.textValue();
        m_scores.addScore(name, score, sec.count());
    }

    int result = m_scores.exec();

    if(result == Result::RESTART)
    {
        emit restartChosen();
        m_scene.clear();
        prepareScene();
        redraw();
    }
    else if(result == Result::QUIT)
    {
        QApplication::quit();
    }
}

void MainWindow::prepareScene()
{
    drawWalls();
    if(GameContants::DRAW_GRID())
    {
        drawGrid();
    }
}

void MainWindow::drawHead(const Model::Point& head)
{
    m_scene.addEllipse(m_fieldSize*head.x + m_delta/2, m_fieldSize*head.y + m_delta/2,
                       m_size, m_size, QPen(Qt::black), QBrush(Qt::green));
    QPointF vertex1;
    QPointF vertex2;
    QPointF vertex3;

    const auto direction = m_game.getDirection();

    const qreal insideDelta = MainWindow::m_delta+2;
    switch(direction)
    {
        case Model::Direction::RIGHT:
        {
            vertex1 = QPointF(m_fieldSize*head.x + insideDelta,
                              m_fieldSize*head.y + insideDelta);
            vertex2 = QPointF(m_fieldSize*head.x + insideDelta,
                              m_fieldSize*head.y + m_fieldSize - insideDelta);
            vertex3 = QPointF(m_fieldSize*head.x + m_fieldSize - insideDelta,
                              m_fieldSize*head.y + m_fieldSize / 2);
            break;
        }
        case Model::Direction::LEFT:
        {
            vertex1 = QPointF(m_fieldSize*head.x + m_fieldSize - insideDelta,
                              m_fieldSize*head.y + insideDelta);
            vertex2 = QPointF(m_fieldSize*head.x + m_fieldSize - insideDelta,
                              m_fieldSize*head.y + m_fieldSize - insideDelta);
            vertex3 = QPointF(m_fieldSize*head.x + insideDelta,
                              m_fieldSize*head.y + m_fieldSize / 2);
            break;
        }
        case Model::Direction::UP:
        {
            vertex1 = QPointF(m_fieldSize*head.x + insideDelta,
                              m_fieldSize*head.y + m_fieldSize - insideDelta);
            vertex2 = QPointF(m_fieldSize*head.x + m_fieldSize - insideDelta,
                              m_fieldSize*head.y + m_fieldSize - insideDelta);
            vertex3 = QPointF(m_fieldSize*head.x + m_fieldSize/2,
                              m_fieldSize*head.y + insideDelta);
            break;
        }
        case Model::Direction::DOWN:
        {
            vertex1 = QPointF(m_fieldSize*head.x + insideDelta,
                              m_fieldSize*head.y + insideDelta);
            vertex2 = QPointF(m_fieldSize*head.x + m_fieldSize - insideDelta,
                              m_fieldSize*head.y + insideDelta);
            vertex3 = QPointF(m_fieldSize*head.x + m_fieldSize/2,
                              m_fieldSize*head.y + m_fieldSize - insideDelta);
            break;
        }
    }

    QPolygonF triangle;
    triangle.append({vertex1, vertex2, vertex3, vertex1});
    m_scene.addPolygon(triangle, QPen(Qt::black), QBrush(Qt::blue));
}

void MainWindow::drawGrid()
{
    for(unsigned x = m_fieldSize; x < m_fullColsSize; x += m_fieldSize)
    {
        m_scene.addLine(x, 1, x, m_fullRowSize-2, QPen(Qt::black));
    }

    for(unsigned y = m_fieldSize; y < m_fullRowSize; y += m_fieldSize)
    {
        m_scene.addLine(1, y, m_fullColsSize-2, y, QPen(Qt::black));
    }
}

void MainWindow::drawWalls()
{
   m_scene.addLine(1, 1, 1, m_fullRowSize-2, QPen(Qt::black));
   m_scene.addLine(1, 1, m_fullColsSize-2, 1, QPen(Qt::black));
   m_scene.addLine(1, m_fullRowSize-2, m_fullColsSize-2,
                   m_fullRowSize-2, QPen(Qt::black));
   m_scene.addLine(m_fullColsSize-2, 1, m_fullColsSize-2,
                   m_fullRowSize-2, QPen(Qt::black));
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

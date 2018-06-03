#include "mainwindow.hpp"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->graphicsView->setScene(&m_scene);

    constexpr unsigned MAIN_WINDOW_OFFSET = 50;

    this->setFixedSize(FULL_ROW_SIZE + MAIN_WINDOW_OFFSET,
                       FULL_COLS_SIZE + MAIN_WINDOW_OFFSET);

    ui->graphicsView->setFixedSize(FULL_ROW_SIZE,
                                   FULL_COLS_SIZE);

    for(unsigned x = FIELD_SIZE; x < FULL_ROW_SIZE; x += FIELD_SIZE)
    {
        m_scene.addLine(x, 2, x, FULL_ROW_SIZE-2, QPen(Qt::black));
    }

    for(unsigned y = FIELD_SIZE; y < FULL_COLS_SIZE; y += FIELD_SIZE)
    {
        m_scene.addLine(2, y, FULL_COLS_SIZE-2, y, QPen(Qt::black));
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

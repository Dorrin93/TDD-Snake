#include "scoreboard.hpp"
#include "ui_scoreboard.h"

ScoreBoard::ScoreBoard(QWidget *parent):
    QDialog(parent, Qt::WindowSystemMenuHint | Qt::WindowTitleHint),
    ui(new Ui::ScoreBoard)
{
    ui->setupUi(this);
    this->setWindowTitle("TDD-Snake Scoreboard");
}

ScoreBoard::~ScoreBoard()
{
    delete ui;
}

void ScoreBoard::restartClicked()
{
    done(Result::RESTART);
}

void ScoreBoard::quitClicked()
{
    done(Result::QUIT);
}

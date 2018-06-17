#include "scoreboard.hpp"
#include "ui_scoreboard.h"

ScoreBoard::ScoreBoard(QWidget *parent):
    QDialog(parent, Qt::WindowSystemMenuHint | Qt::WindowTitleHint),
    ui(new Ui::ScoreBoard)
{
    ui->setupUi(this);
    setWindowTitle("TDD-Snake Scoreboard");
    auto scoreTable = ui->scores;
    scoreTable->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);

    const auto OFFSET = 105;
    setFixedHeight(scoreTable->verticalHeader()->length() + OFFSET);
}

ScoreBoard::~ScoreBoard()
{
    delete ui;
}

void ScoreBoard::addScore(const QString &name, unsigned points, unsigned time)
{
    m_scores.emplace(Score{name, points, time});
    if(m_scores.size() > 10)
    {
        m_scores.erase(m_scores.cbegin());
    }

    refreshTable();
}

void ScoreBoard::restartClicked()
{
    done(Result::RESTART);
}

void ScoreBoard::quitClicked()
{
    done(Result::QUIT);
}

void ScoreBoard::refreshTable()
{
    if(m_scores.size() <= 10)
    {
        ui->scores->setItem(m_scores.size()-1, 0, new QTableWidgetItem("x"));
        auto item1 = new QTableWidgetItem("y");
        item1->setTextAlignment(Qt::AlignCenter);
        ui->scores->setItem(m_scores.size()-1, 1, item1);
        auto item2 = new QTableWidgetItem("z");
        item2->setTextAlignment(Qt::AlignCenter);
        ui->scores->setItem(m_scores.size()-1, 2, item2);
    }

    size_t i = 0;
    for(auto it = m_scores.crbegin(); it != m_scores.crend(); ++it, ++i)
    {
        ui->scores->item(i, 0)->setText(it->name);
        ui->scores->item(i, 1)->setText(QString::number(it->points));
        ui->scores->item(i, 2)->setText(QString::number(it->time));
    }
}

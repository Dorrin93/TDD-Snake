#ifndef SCOREBOARD_HPP
#define SCOREBOARD_HPP

#include <QDialog>
#include <set>

namespace Ui
{
class ScoreBoard;
}

struct Score
{
    QString name;
    unsigned points;
    unsigned time;
};

inline bool operator<(const Score& lhs, const Score& rhs)
{
    return lhs.points == rhs.points ? lhs.time > rhs.time
                                    : lhs.points < rhs.points;
}

enum Result
{
    QUIT = 0,
    RESTART = 1
};

class ScoreBoard : public QDialog
{
    Q_OBJECT

public:
    explicit ScoreBoard(QWidget *parent = 0);
    ~ScoreBoard();

    void addScore(const QString& name, unsigned points, unsigned time);

signals:
    void restart();

private slots:
    void restartClicked();
    void quitClicked();

private:
    void refreshTable();

    Ui::ScoreBoard *ui;
    std::multiset<Score> m_scores;
};

#endif // SCOREBOARD_HPP

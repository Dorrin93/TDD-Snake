#ifndef SETTINGSSCREEN_HPP
#define SETTINGSSCREEN_HPP

#include <QDialog>
#include "constants.hpp"

namespace Ui {
class SettingsScreen;
}

class SettingsScreen : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsScreen(QWidget *parent = 0);
    ~SettingsScreen();

private slots:
    void rowsValueChanged(int value);
    void colsValueChanged(int value);
    void drawGridChanged(bool value);
    void fieldSizeChanged(int value);
    void snakeSpeedChanged(int value);
    void startClicked();

private:
    Ui::SettingsScreen *ui;
};

#endif // SETTINGSSCREEN_HPP

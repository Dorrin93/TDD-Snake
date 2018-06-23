#include "settingsscreen.hpp"
#include "ui_settingsscreen.h"

SettingsScreen::SettingsScreen(QWidget *parent) :
    QDialog(parent, Qt::WindowSystemMenuHint | Qt::WindowTitleHint),
    ui(new Ui::SettingsScreen)
{
    ui->setupUi(this);
    setWindowTitle("TDD-Snake settings");
}

SettingsScreen::~SettingsScreen()
{
    delete ui;
}

void SettingsScreen::rowsValueChanged(int value)
{
    GameContants::ROWS() = value;
    ui->heightBox->setValue(value * GameContants::FIELD_SIZE());
}

void SettingsScreen::colsValueChanged(int value)
{
    GameContants::COLS() = value;
    ui->widthBox->setValue(value * GameContants::FIELD_SIZE());
}

void SettingsScreen::drawGridChanged(bool value)
{
    GameContants::DRAW_GRID() = value;
}

void SettingsScreen::fieldSizeChanged(int value)
{
    GameContants::FIELD_SIZE() = value;
    ui->heightBox->setValue(GameContants::ROWS() * value);
    ui->widthBox->setValue(GameContants::COLS() * value);
}

void SettingsScreen::snakeSpeedChanged(int value)
{
    const unsigned MAX_TIMEOUT = 1000;
    const unsigned TIMEOUT_STEP = 100;
    GameContants::TIMEOUT() = MAX_TIMEOUT - value*TIMEOUT_STEP;
}

void SettingsScreen::startClicked()
{
    done(true);
}

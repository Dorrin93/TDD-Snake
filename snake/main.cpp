#include <QApplication>
#include "mainwindow.hpp"
#include "game.hpp"
#include "grid.hpp"
#include "gamecontroller.hpp"
#include "settingsscreen.hpp"

namespace
{

int toInt(size_t value)
{
    return static_cast<int>(value);
}

}
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    SettingsScreen test;

    test.exec();

    Model::Grid grid(GameContants::COLS(), GameContants::ROWS());
    Model::Snake snake({toInt(GameContants::COLS())/2, toInt(GameContants::ROWS())/2});
    Model::PointGenerator generator(GameContants::COLS()-1, GameContants::ROWS()-1);
    Model::Game game(grid, snake, generator);

    Controller::GameController controller(game);


    controller.start();
    MainWindow window(game);
    QObject::connect(&controller, SIGNAL(updateDone()), &window, SLOT(redraw()));
    QObject::connect(&controller, SIGNAL(gameEnd(std::chrono::seconds, size_t)),
                     &window, SLOT(endGame(std::chrono::seconds, size_t)));
    QObject::connect(&window, SIGNAL(directionChanged(Model::Direction)),
                     &controller, SLOT(changeDirection(Model::Direction)));
    QObject::connect(&window, SIGNAL(restartChosen()),
                     &controller, SLOT(restart()));

    window.show();


    return a.exec();
}

#include <QApplication>
#include "mainwindow.hpp"
#include "game.hpp"
#include "grid.hpp"
#include "gamecontroller.hpp"

int main(int argc, char *argv[])
{
    static_assert(GameContants::FIELD_SIZE > 10, "FIELD_SIZE must be 10 pixels or more");

    Model::Grid grid(GameContants::ROWS, GameContants::COLS);
    Model::Snake snake({GameContants::ROWS/2, GameContants::COLS/2});
    Model::Game game(grid, snake);

    Controller::GameController controller(game);

    QApplication a(argc, argv);

    controller.start();
    MainWindow window(game);
    QObject::connect(&controller, SIGNAL(updateDone()), &window, SLOT(redraw()));
    QObject::connect(&window, SIGNAL(directionChanged(Model::Direction)),
                     &controller, SLOT(changeDirection(Model::Direction)));

    window.show();


    return a.exec();
}

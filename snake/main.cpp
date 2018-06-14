#include <QApplication>
#include "mainwindow.hpp"
#include "game.hpp"
#include "grid.hpp"
#include "gamecontroller.hpp"

int main(int argc, char *argv[])
{
    static_assert(GameContants::FIELD_SIZE > 10, "FIELD_SIZE must be 10 pixels or more");

    Model::Grid grid(GameContants::COLS, GameContants::ROWS);
    Model::Snake snake({GameContants::COLS/2, GameContants::ROWS/2});
    Model::PointGenerator generator(GameContants::COLS-1, GameContants::ROWS-1);
    Model::Game game(grid, snake, generator);

    Controller::GameController controller(game);

    QApplication a(argc, argv);

    controller.start();
    MainWindow window(game);
    QObject::connect(&controller, SIGNAL(updateDone()), &window, SLOT(redraw()));
    QObject::connect(&controller, SIGNAL(gameEnd(std::chrono::seconds, size_t)),
                     &window, SLOT(endGame(std::chrono::seconds, size_t)));
    QObject::connect(&window, SIGNAL(directionChanged(Model::Direction)),
                     &controller, SLOT(changeDirection(Model::Direction)));

    window.show();


    return a.exec();
}

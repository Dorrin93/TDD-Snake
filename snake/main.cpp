#include "mainwindow.hpp"
#include <QApplication>

int main(int argc, char *argv[])
{
    static_assert(FIELD_SIZE > 10, "FIELD_SIZE must be 10 pixels or more");

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}

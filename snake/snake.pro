#-------------------------------------------------
#
# Project created by QtCreator 2018-06-02T12:18:31
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = snake
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += Include

SOURCES += \
    main.cpp \
    Source/game.cpp \
    Source/gamecontroller.cpp \
    Source/grid.cpp \
    Source/mainwindow.cpp \
    Source/snake.cpp \
    Source/pointgenerator.cpp \
    Source/scoreboard.cpp \
    Source/settingsscreen.cpp

HEADERS += \
    Include/constants.hpp \
    Include/flattenvector.hpp \
    Include/game.hpp \
    Include/gamecontroller.hpp \
    Include/grid.hpp \
    Include/mainwindow.hpp \
    Include/snake.hpp \
    Include/point.hpp \
    Include/pointgenerator.hpp \
    Include/scoreboard.hpp \
    Include/settingsscreen.hpp

FORMS += \
    mainwindow.ui \
    scoreboard.ui \
    settingsscreen.ui

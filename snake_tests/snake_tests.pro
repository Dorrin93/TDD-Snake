include(gtest_dependency.pri)

TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG += thread
CONFIG -= qt

INCLUDEPATH += ../snake/Include Mocks
DEPENDPATH += $${INCLUDEPATH}
VPATH += ../snake/Source Mocks


HEADERS += \
    gridtests.hpp \
    gametests.hpp \
    Mocks/gridmock.hpp \
    snaketests.hpp \
    Mocks/snakemock.hpp \
    Mocks/pointgeneratormock.hpp

SOURCES += \
        *.cpp \
        ../snake/Source/grid.cpp \
        ../snake/Source/game.cpp \
        ../snake/Source/snake.cpp

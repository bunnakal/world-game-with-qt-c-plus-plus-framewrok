#-------------------------------------------------
#
# Project created by QtCreator 2014-11-29T19:26:57
#
#-------------------------------------------------

QT       += core gui
QMAKE_CXXFLAGS +=-std=c++11
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WorldGame
TEMPLATE = app


SOURCES += main.cpp\
        worldgame.cpp \
    world.cpp \
    worldscene.cpp \
    worldprotagonist.cpp \
    woldmodel.cpp \
    worldview.cpp \
    worldprogressbar.cpp

HEADERS  += worldgame.h \
    world_global.h \
    world.h \
    worldscene.h \
    worldprotagonist.h \
    worldmodel.h \
    worldview.h \
    worldprogressbar.h

FORMS    += worldgame.ui

RESOURCES += \
    MyResources.qrc

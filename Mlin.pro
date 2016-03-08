#-------------------------------------------------
#
# Project created by QtCreator 2016-03-08T12:59:04
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Mlin
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    src/board.cpp \
    src/game.cpp

HEADERS  += mainwindow.h \
    board.h \
    game.h

FORMS    += mainwindow.ui

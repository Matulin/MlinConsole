#-------------------------------------------------
#
# Project created by QtCreator 2016-03-20T13:28:11
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Mlin
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    src/board.cpp \
    src/game.cpp \
    src/graphics.cpp \
    src/interface.cpp \
    src/menu.cpp \
    src/toolbar.cpp \
    src/options.cpp

HEADERS  += mainwindow.h \
    board.h \
    game.h \
    graphics.h \
    interface.h \
    menu.h \
    toolbar.h \
    options.h

FORMS    += mainwindow.ui

#include "mainwindow.h"
#include <QApplication>
#include <QtGui>
#include <game.h>
#include <board.h>

int main(int argc, char *argv[])
{
    struct gameData data;
    data.displayBoard();

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}

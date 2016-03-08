#include "mainwindow.h"
#include <QApplication>
#include <QLabel>
#include "board.h"
#include "game.h"

int main(int argc, char *argv[])
{
    struct gameData data;
    initGame(&data);
    displayBoard(data.board);
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}

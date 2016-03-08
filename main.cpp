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

    QApplication app(argc, argv);
    QLabel *label = new QLabel("This is a test!");
    label->show();
    return app.exec();
}

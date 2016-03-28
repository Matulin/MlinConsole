#include "mainwindow.h"
#include <QApplication>
#include <QtGui>
#include <game.h>
#include <board.h>
#include <graphics.h>
#include <QHBoxLayout>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    std::cout << "Program begins" << std::endl;

   MainWindow w;



    w.show();

    return a.exec();
}

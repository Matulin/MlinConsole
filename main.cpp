#include "mainwindow.h"
#include <QApplication>
#include <QtGui>
#include <game.h>
#include <board.h>
#include <graphics.h>
#include <QHBoxLayout>
#include "interface.h"



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // MainWindow w;
    interfaceWindow * w = new interfaceWindow(&a);



    w->show();

    return a.exec();
}

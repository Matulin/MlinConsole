#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
   gameData * gameData2 = new gameData;
   QHBoxLayout * appBox = new QHBoxLayout;
   setLayout(appBox);
   appBox->addWidget(gameData2->boardWidget);

}

MainWindow::~MainWindow()
{

}

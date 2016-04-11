#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
   class gameData gameData;
   QHBoxLayout * appBox = new QHBoxLayout;
   setLayout(appBox);
   appBox->addWidget(gameData.boardWidget);





}

MainWindow::~MainWindow()
{

}

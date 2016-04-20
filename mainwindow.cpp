#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QApplication * thisApp, QWidget *parent)
    : QWidget(parent)
{
   parentApplication = thisApp;
   startUpMenu = new mainMenu(this);
   //interfaceWindow * w = new interfaceWindow(parentApplication);
   setLayout(startUpMenu);
}

MainWindow::~MainWindow()
{

}

void MainWindow::startGame()
{
    interfaceWindow * w = new interfaceWindow(parentApplication);
    startUpMenu->~mainMenu();
    setLayout(w);
}

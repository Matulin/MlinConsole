#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QApplication * thisApp, QWidget *parent)
    : QWidget(parent)
{
   parentApplication = thisApp;
   //startUpMenu = new mainMenu(this);
   interfaceWindow * w = new interfaceWindow(parentApplication);
   setLayout(w);
}

MainWindow::~MainWindow()
{

}

void MainWindow::startGame()
{
    startUpMenu->~mainMenu();
    interfaceWindow * w = new interfaceWindow(parentApplication);
    w->setMenuBar(w->toolbar);
    setLayout(w);
}

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
   startUpMenu = new mainMenu(this);
   setLayout(startUpMenu);
}

MainWindow::~MainWindow()
{

}

void MainWindow::startGame()
{
    interfaceWindow * w = new interfaceWindow();
    startUpMenu->deleteMainMenu();
    setLayout(w);
    w->toolbar->setVisible(TRUE);
}

void MainWindow::loadGame()
{
    std::cout << "Loading" << std::endl;
}

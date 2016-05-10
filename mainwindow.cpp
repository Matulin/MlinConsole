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
    interfaceWindow * w = new interfaceWindow(this);
    w->toolbar->options->loadOption(true);

}

void MainWindow::exitApp()
{
    QApplication::quit();
}

#ifndef MENU_H
#define MENU_H

#include <QVBoxLayout>
#include <QtGui>
#include <QPushButton>
#include "options.h"
#include "mainwindow.h"

class MainWindow;

class mainMenu : public QVBoxLayout
{
   Q_OBJECT

public:
    explicit mainMenu(MainWindow * givenWindow);
    ~mainMenu();

private:
    QPushButton * newGame;
    QPushButton * loadGame;
    QPushButton * howToPlay;
    QPushButton * settings;
    QPushButton * exitButton;
    MainWindow * parentWindow;

};

#endif // MENU_H

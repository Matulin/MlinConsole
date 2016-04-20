#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include "board.h"
#include "game.h"
#include <QtGui>
#include <QHBoxLayout>
#include "interface.h"
#include "menu.h"

class interfaceWindow;
class mainMenu;


class MainWindow : public QWidget
{
    Q_OBJECT

public:

    explicit MainWindow(QApplication * thisApp, QWidget *parent = 0);
    QApplication * parentApplication;
    ~MainWindow();
    mainMenu * startUpMenu;

public slots:
    void startGame();
};

#endif // MAINWINDOW_H

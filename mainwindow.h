#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <board.h>
#include <game.h>
#include <QtGui>
#include <QHBoxLayout>
#include <interface.h>

class interfaceWindow;


class MainWindow : public QWidget
{
    Q_OBJECT



public:

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

};

#endif // MAINWINDOW_H

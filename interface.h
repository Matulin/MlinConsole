#ifndef INTERFACE_H
#define INTERFACE_H

#include "board.h"

class gameData;

class interfaceWindow : public QWidget
{
    Q_OBJECT

public:

    explicit interfaceWindow(QWidget *parent = 0);
    explicit interfaceWindow(class gameData * data, QWidget *parent = 0);
    ~interfaceWindow();
    class gameData * thisGameData;
    QVBoxLayout * gameSideBar;
    QHBoxLayout * gameWindow;
    initInterfaceWidgets();

};


#endif // INTERFACE_H

#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <QAction>
#include <QtGui>
#include <QTCore>
#include <QMenu>
#include <QMenuBar>
#include <QHBoxLayout>
#include <QAction>
#include "interface.h"
#include "options.h"

class optionFunctions;

class gameToolbar : public QWidget
{
    Q_OBJECT

public:

    explicit gameToolbar(optionFunctions * optionClass);
    ~gameToolbar();

public:
    QMenuBar * gameMenu;
    QHBoxLayout * toolbarLayout;
    optionFunctions * options;

    QAction * restartButton;
    QAction * saveButton;
    QAction * saveAsButton;
    QAction * saveAndExitButton;
    QAction * exitButton;
    QMenu * gameButton;


    QAction * languageButton;
    QMenu * optionButton;

private slots:



};


#endif // TOOLBAR_H


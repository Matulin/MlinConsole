#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <QAction>
#include <QtGui>
#include <QTCore>
#include <QMenu>
#include <QHBoxLayout>

class gameToolbar : public QWidget
{
    Q_OBJECT

public:

    explicit gameToolbar(QWidget *parent = 0);
    ~gameToolbar();

public:
    QHBoxLayout * toolbarLayout;
    QAction * restartButton;
    QAction * saveButton;
    QMenu * gameMenu;
};


#endif // TOOLBAR_H


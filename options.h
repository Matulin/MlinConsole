#ifndef OPTIONS_H
#define OPTIONS_H

#include <QApplication>
#include <QtCore>
#include <QtGui>
#include <board.h>

class QApplication;
class gameData;

class optionFunctions : public QWidget
{
   Q_OBJECT
public:
    explicit optionFunctions(gameData * gameData, QApplication * thisApp);
public:
    QApplication * runningApp;
    gameData * thisGameData;

public slots:
    void testFunction();
    void exitApp();
    void restartGame();
};

#endif // OPTIONS_H

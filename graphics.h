#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <iostream>
#include <QLabel>
#include <QMouseEvent>
#include <QtGui>
#include <QTCore>
#include <board.h>


struct position;
class gameData;

class squareGraphic : public QLabel
{
    Q_OBJECT
public:

    explicit squareGraphic(struct position * squarePosition, class gameData * data, QLabel *parent = 0);
    explicit squareGraphic(QLabel *parent = 0);
   ~squareGraphic();

public:
    unsigned int arrayXCoord;
    unsigned int arrayYCoord;
    unsigned int arrayLayNum;
    struct position * thisPosition;
    class gameData * gameData;
    void squareClicked();
    void setCoords(unsigned int layNum, unsigned int XCoord, unsigned int YCoord);
    bool tokenCheck;

protected:
     void mousePressEvent(QMouseEvent *);

signals:
    void clicked();




};

#endif // GRAPHICS_H

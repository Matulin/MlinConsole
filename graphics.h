#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <iostream>
#include <QLabel>
#include <QMouseEvent>
#include <QtGui>
#include <QTCore>
#include <board.h>
#include <QVBoxLayout>
#include <QHBoxLayout>


// struct position;
class gameData;

class squareGraphic : public QLabel
{
    Q_OBJECT
public:

    explicit squareGraphic(struct position * squarePosition, class gameData * data, QLabel *parent = 0);
    explicit squareGraphic(class gameData * data, QLabel *parent = 0);
    explicit squareGraphic(QLabel *parent = 0);
   ~squareGraphic();

public:
    unsigned int arrayXCoord;
    unsigned int arrayYCoord;
    unsigned int arrayLayNum;
    QPixmap * defaultImg;
    QPixmap * hoverImg;
    struct position * thisPosition;
    class gameData * gameData;
    void squareClicked();
    void setCoords(unsigned int layNum, unsigned int XCoord, unsigned int YCoord);
    void setDefaults(QPixmap * defaultImage, QPixmap * hoverImage);
    bool tokenCheck;
    gameLoop();

protected:
     void mousePressEvent(QMouseEvent *);
     void enterEvent(QEvent *);
     void leaveEvent(QEvent *);

signals:
    void clicked();


};

#endif // GRAPHICS_H

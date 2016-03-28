#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <iostream>
#include <QLabel>
#include <QMouseEvent>
#include <QtGui>
#include <QTCore>


class squareGraphic : public QLabel
{
    Q_OBJECT
public:

    explicit squareGraphic(QLabel *parent = 0);
    ~squareGraphic();

public:
    unsigned int arrayXCoord;
    unsigned int arrayYCoord;
    unsigned int arrayLayNum;

    void setCoords(unsigned int layNum, unsigned int XCoord, unsigned int YCoord);

protected:
     void mousePressEvent(QMouseEvent *);

signals:
    void clicked();

public slots:
    void functionTest();



};

#endif // GRAPHICS_H

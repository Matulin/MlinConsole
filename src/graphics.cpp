#include <graphics.h>

squareGraphic::squareGraphic(struct position * squarePosition, class gameData * data, QLabel *parent)
    : QLabel(parent)
{
    tokenCheck = true;
    thisPosition = squarePosition;
    gameData = data;

}

squareGraphic::squareGraphic(QLabel *parent)
    : QLabel(parent)
{
    tokenCheck = false;
}

squareGraphic::~squareGraphic()
{

}

void squareGraphic::setCoords(unsigned int layNum, unsigned int XCoord, unsigned int YCoord)
{

    arrayLayNum = layNum;
    arrayXCoord = XCoord;
    arrayYCoord = YCoord;

}

void squareGraphic::setDefaults(QPixmap * defaultImage, QPixmap * hoverImage)
{
    defaultImg = defaultImage;
    hoverImg = hoverImage;
    this->setPixmap(*defaultImg);
}

void squareGraphic::mousePressEvent(QMouseEvent *)
{
    if(tokenCheck == true)
    {
        gameData->gameFunction(arrayXCoord, arrayYCoord, arrayLayNum);

    }
}

void squareGraphic::enterEvent(QEvent *)
{
    if(((tokenCheck == true) && ((thisPosition->colour == noToken)) && (gameData->gameStatus == placing)))
    {
        this->setPixmap(*hoverImg);
    }
}

void squareGraphic::leaveEvent(QEvent *)
{
    if(((tokenCheck == true) && ((thisPosition->colour == noToken)) && (gameData->gameStatus == placing)))
    {
        this->setPixmap(*defaultImg);
    }
}

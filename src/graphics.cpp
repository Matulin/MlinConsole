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

void squareGraphic::mousePressEvent(QMouseEvent *)
{
    if(tokenCheck == true)
    {

        //std::cout << arrayLayNum << std::endl;
        //std::cout << thisPosition->colour << std::endl;
        // gameData->displayBoard();
        // gameData->placePiece(arrayLayNum, arrayXCoord, arrayYCoord, blackToken);
        emit clicked();
    }
}

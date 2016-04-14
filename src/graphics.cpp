#include "graphics.h"

squareGraphic::squareGraphic(struct position * squarePosition, class gameData * data, QLabel *parent)
    : QLabel(parent)
{
    tokenCheck = true;
    thisPosition = squarePosition;
    gameData = data;

}

squareGraphic::squareGraphic(class gameData * data, QLabel *parent)
    : QLabel(parent)
{
    gameData = data;
    tokenCheck = false;
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
   else if((gameData->gameStatus == moving) && (gameData->selectedToken != noToken))
    {
        gameData->selectedToken = noToken;
        if(gameData->selectedPosition.colour == blackToken)
        {
            gameData->selectedPosition.locImg->setPixmap(*gameData->tokenImage.blackTokenMap);
        }
        else if(gameData->selectedPosition.colour == whiteToken)
        {
            gameData->selectedPosition.locImg->setPixmap(*gameData->tokenImage.whiteTokenMap);
        }
        gameData->selectedPosition = gameData->board[1][1][1];

    }
}

void squareGraphic::enterEvent(QEvent *)
{
    if(tokenCheck == true)
    {
        if((thisPosition->colour == noToken) && (gameData->gameStatus == placing))
        {
            this->setPixmap(*hoverImg);
        }
        else if(((gameData->gameStatus == moving) && (gameData->selectedToken == noToken)) && ((thisPosition->colour == gameData->currentTurn) && (gameData->checkForMove(thisPosition->arrayLayNum, thisPosition->arrayXCoord, thisPosition->arrayYCoord) == true)))
        {
            if(thisPosition->colour == blackToken)
            {
                this->setPixmap(*(gameData->tokenImage.blackTokenHoverMap));
            }
            else if(thisPosition->colour == whiteToken)
            {
                this->setPixmap(*(gameData->tokenImage.whiteTokenHoverMap));
            }
        }
        else if(((gameData->gameStatus == moving) && (gameData->selectedToken != noToken)) && (thisPosition->colour == noToken))
        {
            if(gameData->valMove(gameData->selectedPosition.arrayXCoord, gameData->selectedPosition.arrayYCoord, gameData->selectedPosition.arrayLayNum, thisPosition->arrayXCoord, thisPosition->arrayYCoord, thisPosition->arrayLayNum))
            {
                this->setPixmap(*hoverImg);
            }

        }
        else if(gameData->gameStatus == taking)
        {
            if((thisPosition->colour == blackToken) && ((gameData->currentTurn == whiteToken) && (thisPosition->mlinStatus < 1)))
            {
                this->setPixmap(*gameData->tokenImage.blackTokenDeleteMap);
            }
            else if((thisPosition->colour == whiteToken) && ((gameData->currentTurn == blackToken) && (thisPosition->mlinStatus < 1)))
            {
                this->setPixmap(*gameData->tokenImage.whiteTokenDeleteMap);
            }
        }
    }
}

void squareGraphic::leaveEvent(QEvent *)
{
    if(tokenCheck == true)
    {
        if((thisPosition->colour == noToken) && (gameData->gameStatus == placing))
        {
            this->setPixmap(*defaultImg);
        }
        else if(((gameData->gameStatus == moving) && (gameData->selectedToken == noToken)) && (thisPosition->colour == gameData->currentTurn))
        {
            if(thisPosition->colour == blackToken)
            {
                if(thisPosition->mlinStatus < 1)
                    this->setPixmap(*(gameData->tokenImage.blackTokenMap));
                else
                    this->setPixmap(*(gameData->tokenImage.blackTokenMlinMap));
            }
            else if(thisPosition->colour == whiteToken)
            {
                if(thisPosition->mlinStatus < 1)
                    this->setPixmap(*(gameData->tokenImage.whiteTokenMap));
                else
                    this->setPixmap(*(gameData->tokenImage.whiteTokenMlinMap));
            }
        }
        else if(((gameData->gameStatus == moving) && (gameData->selectedToken != noToken)) && (thisPosition->colour == noToken))
        {
            if(gameData->valMove(gameData->selectedPosition.arrayXCoord, gameData->selectedPosition.arrayYCoord, gameData->selectedPosition.arrayLayNum, thisPosition->arrayXCoord, thisPosition->arrayYCoord, thisPosition->arrayLayNum))
            {
                this->setPixmap(*defaultImg);
            }
        }
        else if(gameData->gameStatus == taking)
        {
            if((thisPosition->colour == blackToken) && ((gameData->currentTurn == whiteToken) && (thisPosition->mlinStatus < 1)))
            {
                if(thisPosition->mlinStatus < 1)
                    this->setPixmap(*(gameData->tokenImage.blackTokenMap));
                else
                    this->setPixmap(*(gameData->tokenImage.blackTokenMlinMap));
            }
            else if((thisPosition->colour == whiteToken) && ((gameData->currentTurn == blackToken) && (thisPosition->mlinStatus < 1)))
            {
                if(thisPosition->mlinStatus < 1)
                    this->setPixmap(*(gameData->tokenImage.whiteTokenMap));
                else
                    this->setPixmap(*(gameData->tokenImage.whiteTokenMlinMap));
            }
        }
    }
}

#include "game.h"

gameData::gameData(interfaceWindow * parentWindow)
{

    gameStatus = placing;
    currentTurn = blackToken;
    blackPieces.piecesOnBoard = 0;
    blackPieces.piecesUnplaced = numPieces;
    blackPieces.piecesTaken = 0;
    whitePieces.piecesOnBoard = 0;
    whitePieces.piecesUnplaced = numPieces;
    whitePieces.piecesTaken = 0;
    selectedToken = noToken;
    outerWindow = parentWindow;

    // These will be converted to pngs to preserve image quality
    tokenImage.blackTokenMap = new QPixmap("resources/blackToken.jpg");
    tokenImage.whiteTokenMap = new QPixmap("resources/whiteToken.jpg");
    tokenImage.emptyTokenMap = new QPixmap("resources/blankSquare.jpg");
    tokenImage.whiteTokenMlinMap = new QPixmap("resources/whiteTokenMlin.png");
    tokenImage.blackTokenMlinMap = new QPixmap("resources/blackTokenMlin.png");

    tokenImage.whiteTokenHoverMap = new QPixmap("resources/whiteTokenHover.png");
    tokenImage.blackTokenHoverMap = new QPixmap("resources/blackTokenHover.png");
    tokenImage.whiteTokenSelectMap = new QPixmap("resources/whiteTokenSelect.jpg");
    tokenImage.blackTokenSelectMap = new QPixmap("resources/blackTokenSelect.jpg");
    tokenImage.blackTokenDeleteMap = new QPixmap("resources/blackTokenDelete.png");
    tokenImage.whiteTokenDeleteMap = new QPixmap("resources/whiteTokenDelete.png");

    tokenImage.horizontalLineMap = new QPixmap("resources/horizontalLine.jpg");
    tokenImage.verticalLineMap = new QPixmap("resources/verticalLine.jpg");
    tokenImage.cornerBottomLeftMap = new QPixmap("resources/cornerBottomLeft.jpg");
    tokenImage.cornerBottomRightMap = new QPixmap("resources/cornerBottomRight.jpg");
    tokenImage.cornerTopLeftMap = new QPixmap("resources/cornerTopLeft.jpg");
    tokenImage.cornerTopRightMap = new QPixmap("resources/cornerTopRight.jpg");
    tokenImage.intersectionBottomMap = new QPixmap("resources/intersectionBottom.jpg");
    tokenImage.intersectionTopMap = new QPixmap("resources/intersectionTop.jpg");
    tokenImage.intersectionBottomMap = new QPixmap("resources/intersectionBottom.jpg");
    tokenImage.intersectionLeftMap = new QPixmap("resources/intersectionLeft.jpg");
    tokenImage.intersectionRightMap = new QPixmap("resources/intersectionRight.jpg");
    tokenImage.intersectionMiddleMap = new QPixmap("resources/intersectionMiddle.jpg");


    tokenImage.horizontalLineHoverMap = new QPixmap("resources/horizontalLineHover.jpg");
    tokenImage.verticalLineHoverMap = new QPixmap("resources/verticalLineHover.jpg");
    tokenImage.cornerBottomLeftHoverMap = new QPixmap("resources/cornerBottomLeftHover.jpg");
    tokenImage.cornerBottomRightHoverMap = new QPixmap("resources/cornerBottomRightHover.jpg");
    tokenImage.cornerTopLeftHoverMap = new QPixmap("resources/cornerTopLeftHover.jpg");
    tokenImage.cornerTopRightHoverMap = new QPixmap("resources/cornerTopRightHover.jpg");
    tokenImage.intersectionBottomHoverMap = new QPixmap("resources/intersectionBottomHover.jpg");
    tokenImage.intersectionTopHoverMap = new QPixmap("resources/intersectionTopHover.jpg");
    tokenImage.intersectionBottomHoverMap = new QPixmap("resources/intersectionBottomHover.jpg");
    tokenImage.intersectionLeftHoverMap = new QPixmap("resources/intersectionLeftHover.jpg");
    tokenImage.intersectionRightHoverMap = new QPixmap("resources/intersectionRightHover.jpg");
    tokenImage.intersectionMiddleHoverMap = new QPixmap("resources/intersectionMiddleHover.jpg");



    initBoard();
    initBoardWidget();
}

bool gameData::gameFunction(unsigned int arrayXCoord, unsigned int arrayYCoord, unsigned int arrayLayNum)
{
    outerWindow->messageBox2->clear();
    outerWindow->messageBox3->clear();
    enum posColour currentColour;
    bool movedBool = false;
    currentColour = currentTurn;
    if((gameStatus == taking) && (board[arrayLayNum][arrayXCoord][arrayYCoord].mlinStatus < 1))
    {
        if(takeToken(arrayXCoord, arrayYCoord, arrayLayNum))
        {
            movedBool = true;
        }

    }
    if(gameStatus == placing)
    {
        if(valPos(arrayXCoord, arrayYCoord, arrayLayNum) == false)
        {
            return false;
        }
        else
        {
            if(placePiece(arrayXCoord, arrayYCoord, arrayLayNum, currentColour))
            {
                if(checkForNewMlin(arrayXCoord, arrayYCoord, arrayLayNum) < 1)
                {
                    movedBool = true;
                }
            }
        }
    }

    else if(gameStatus == moving)
    {
        if(moveSelect(arrayXCoord, arrayYCoord, arrayLayNum, currentColour))
        {
            if(checkForNewMlin(arrayXCoord, arrayYCoord, arrayLayNum) < 1)
            {
                movedBool = true;
            }

        }
    }
    if((gameStatus == taking) && (movedBool == true))
    {
        //  If it should be "moving" instead, it'll change to that in changeTurns()
        gameStatus = placing;
    }

    if(movedBool == true)
    {
        changeTurns();
    }
    outerWindow->setInterfaceWidgets();
    return true;
}

bool gameData::moveSelect(unsigned int arrayXCoord, unsigned int arrayYCoord, unsigned int arrayLayNum, enum posColour currentColour)
{
    if(selectedToken == noToken)
    {
        if((board[arrayLayNum][arrayXCoord][arrayYCoord].colour != currentColour) && (checkForMove(arrayLayNum, arrayXCoord, arrayYCoord) == false))
        {
            return false;
        }
        else
        {
            selectedToken = board[arrayLayNum][arrayXCoord][arrayYCoord].colour;
            selectedPosition = board[arrayLayNum][arrayXCoord][arrayYCoord];
            if(currentColour == blackToken)
            {
                selectedPosition.locImg->setPixmap(*tokenImage.blackTokenSelectMap);
            }
            else if(currentColour == whiteToken)
            {
                selectedPosition.locImg->setPixmap(*tokenImage.whiteTokenSelectMap);
            }
            return false;
        }
    }
    else if((selectedToken == whiteToken) || (selectedToken == blackToken))
    {
        if(board[arrayLayNum][arrayXCoord][arrayYCoord].colour != noToken)
        {
            return false;
        }
        else
        {

            return moveToken(selectedPosition.arrayXCoord, selectedPosition.arrayYCoord, selectedPosition.arrayLayNum, arrayXCoord, arrayYCoord, arrayLayNum, selectedToken);
        }
    }
    return false;
}

bool gameData::valMove(int oldx, int oldy, int oldlay, int newx, int newy, int newlay)
{
    if(valPos(newx, newy, newlay) == false)
    {
        return false;
    }

    // Confirms that neither position is an invalid position (i.e. the centre of a layer)
    if((board[oldlay][oldx][oldy].type == centre) || (board[newlay][newx][newy].type == centre))
    {
        return false;
    }

    // Confirms that the two positions aren't exactly the same
    if(((oldx == newx) && (oldy == newy)) && (oldlay == newlay))
    {
        return false;
    }

    // If two positions have the same x and y coordinates and their layer numbers are one off, they're next to each other between the layers if they're intersections
    if((oldx == newx) && (oldy == newy))
    {
        if(board[oldlay][oldx][oldy].type == intersection)
        {
            if((newlay - oldlay == 1) || (oldlay - newlay == 1))
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }

    }

    // Makes sure positions are in the same layer
    if(oldlay != newlay)
    {
        return false;
    }

    // Checks whether the x values are next to each other in the same layer
    if((newx - oldx == 1) || (oldx - newx == 1))
    {
        if(oldy == newy)
        {
            return true;
        }
    }
    if((newy - oldy == 1) || (oldy - newy == 1))
    {
        if(oldx == newx)
        {
            return true;
        }
        else
        {
            return false;
        }
    }


    return false;
}

bool gameData::placePiece(unsigned int xcoord, unsigned int ycoord, unsigned int lay, enum posColour newToken)
{


    board[lay][xcoord][ycoord].colour = newToken;
    board[lay][xcoord][ycoord].locImg->setPixmap(*(tokenImage.blackTokenMap));
    if(newToken == blackToken)
    {
        blackPieces.piecesOnBoard++;
        blackPieces.piecesUnplaced--;
        board[lay][xcoord][ycoord].locImg->setPixmap(*(tokenImage.blackTokenMap));
        return true;
    }
    else if(newToken == whiteToken)
    {
        whitePieces.piecesOnBoard++;
        whitePieces.piecesUnplaced--;
        board[lay][xcoord][ycoord].locImg->setPixmap(*(tokenImage.whiteTokenMap));
        return true;
    }
    return false;
}

/*bool position::placePiece(enum posColour newToken)
{
    if(posColour != noToken)
    {
        return false;
    }
    colour = newToken;

    if(newToken == blackToken)
    {
        gameData.blackPieces.piecesOnBoard++;
        gameData.blackPieces.piecesUnplaced--;
        locImg->setPixmap(*(tokenImage.blackTokenMap));
        return true;
    }
    else if(newToken == whiteToken)
    {
        gameData.whitePieces.piecesOnBoard++;
        gameData.whitePieces.piecesUnplaced--;
        locImg->setPixmap(*(tokenImage.whiteTokenMap));
        return true;
    }
    return false;
}*/


// When all the tokens have been placed, each player takes turns moving a piece one position.
// Attempting to move a token outside the size of the array from a middle-position will result in moving the piece to the next layer.
// A player cannot of course move outwards from the outer-most layer, or inwards from the inner-most layer.
// It is also impossible to move between layers from the corners of a layer.
bool gameData::moveToken(int oldx, int oldy, int oldlay, int newx, int newy, int newlay, enum posColour newToken)
{

    if(valMove(oldx, oldy, oldlay, newx, newy, newlay) != true)
    {

        return false;
    }
    /* board[arrayLayNum][arrayXCoord][arrayYCoord].colour = selectedToken;
    selectedPosition.colour = noToken;
    selectedToken = noToken;*/
    removeMlin(oldx, oldy, oldlay);
    board[oldlay][oldx][oldy].colour = noToken;
    board[newlay][newx][newy].colour = newToken;

    board[oldlay][oldx][oldy].locImg->setPixmap(*board[oldlay][oldx][oldy].locImg->defaultImg);
    if(newToken == blackToken)
    {
        board[newlay][newx][newy].locImg->setPixmap(*tokenImage.blackTokenMap);
    }
    else if(newToken == whiteToken)
    {
        board[newlay][newx][newy].locImg->setPixmap(*tokenImage.whiteTokenMap);
    }
    return true;
}

int gameData::checkForNewMlin(unsigned int xcoord, unsigned int ycoord, unsigned int laynum)
{
    int mlin = 0; // It's possible for a single move to make 0, 1 or 2 mlins.
    if((board[laynum][xcoord][0].colour == board[laynum][xcoord][2].colour) && (board[laynum][xcoord][0].colour == board[laynum][xcoord][1].colour))
    {
        board[laynum][xcoord][0].mlinStatus++;
        board[laynum][xcoord][1].mlinStatus++;
        board[laynum][xcoord][2].mlinStatus++;
        mlin++;
        if(board[laynum][xcoord][ycoord].colour == blackToken)
        {
            board[laynum][xcoord][0].locImg->setPixmap(*tokenImage.blackTokenMlinMap);
            board[laynum][xcoord][1].locImg->setPixmap(*tokenImage.blackTokenMlinMap);
            board[laynum][xcoord][2].locImg->setPixmap(*tokenImage.blackTokenMlinMap);
        }
        else if(board[laynum][xcoord][ycoord].colour == whiteToken)
        {
            board[laynum][xcoord][0].locImg->setPixmap(*tokenImage.whiteTokenMlinMap);
            board[laynum][xcoord][1].locImg->setPixmap(*tokenImage.whiteTokenMlinMap);
            board[laynum][xcoord][2].locImg->setPixmap(*tokenImage.whiteTokenMlinMap);
        }


    }
    if((board[laynum][0][ycoord].colour == board[laynum][2][ycoord].colour) && (board[laynum][0][ycoord].colour == board[laynum][1][ycoord].colour))
    {
        board[laynum][0][ycoord].mlinStatus++;
        board[laynum][1][ycoord].mlinStatus++;
        board[laynum][2][ycoord].mlinStatus++;
        mlin++;
        if(board[laynum][xcoord][ycoord].colour == blackToken)
        {
            board[laynum][0][ycoord].locImg->setPixmap(*tokenImage.blackTokenMlinMap);
            board[laynum][1][ycoord].locImg->setPixmap(*tokenImage.blackTokenMlinMap);
            board[laynum][2][ycoord].locImg->setPixmap(*tokenImage.blackTokenMlinMap);
        }
        else if(board[laynum][xcoord][ycoord].colour == whiteToken)
        {
            board[laynum][0][ycoord].locImg->setPixmap(*tokenImage.whiteTokenMlinMap);
            board[laynum][1][ycoord].locImg->setPixmap(*tokenImage.whiteTokenMlinMap);
            board[laynum][2][ycoord].locImg->setPixmap(*tokenImage.whiteTokenMlinMap);
        }
    }
    if(board[laynum][xcoord][ycoord].type == intersection)
    {
            // Checks for a mlin across the layers
            if((board[0][xcoord][ycoord].colour == board[1][xcoord][ycoord].colour) && (board[1][xcoord][ycoord].colour == board[2][xcoord][ycoord].colour))
            {
                board[0][xcoord][ycoord].mlinStatus++;
                board[1][xcoord][ycoord].mlinStatus++;
                board[2][xcoord][ycoord].mlinStatus++;
                mlin++;
                if(board[laynum][xcoord][ycoord].colour == blackToken)
                {

                    board[0][xcoord][ycoord].locImg->setPixmap(*tokenImage.blackTokenMlinMap);
                    board[1][xcoord][ycoord].locImg->setPixmap(*tokenImage.blackTokenMlinMap);
                    board[2][xcoord][ycoord].locImg->setPixmap(*tokenImage.blackTokenMlinMap);
                }
                else if(board[laynum][xcoord][ycoord].colour == whiteToken)
                {
                    board[0][xcoord][ycoord].locImg->setPixmap(*tokenImage.whiteTokenMlinMap);
                    board[1][xcoord][ycoord].locImg->setPixmap(*tokenImage.whiteTokenMlinMap);
                    board[2][xcoord][ycoord].locImg->setPixmap(*tokenImage.whiteTokenMlinMap);
                }
            }
    }
    if(mlin > 0)
    {
        if(currentTurn == blackToken)
        {
            outerWindow->messageBox2->setText("Black Mlins!");
        }
        else if(currentTurn == whiteToken)
        {
            outerWindow->messageBox2->setText("White Mlins!");
        }

        if(!checkForTakableToken())
        {

            outerWindow->messageBox3->setText("All of the opponent's pieces are in mlin");
            changeTurns();
        }
        else
            gameStatus = taking;
    }

    return mlin;
}

// First, this checks if there are any three tokens of the same type lined up. If so, that player gets a "mlin" and can choose to take a piece.
// If a player cannot move any pieces anywhere, or they have less than two pieces left on the board (after having placed all their pieces), they lose the game.
enum posColour gameData::checkForMlin()
{
    // Checks for a mlin only in a single layer
    for(unsigned int count = 0; count < numOfLayers; count++)
    {
        for(unsigned int count2 = 0; count2 < boardLayerHeight; count2++)
        {
            if((board[count][count2][0].colour == board[count][count2][1].colour) && (board[count][count2][0].colour == board[count][count2][2].colour))
            {
                if(board[count][count2][0].colour != noToken)
                {
                    return board[count][count2][0].colour;
                }
            }
            if((board[count][0][count2].colour == board[count][1][count2].colour) && (board[count][0][count2].colour == board[count][2][count2].colour))
            {
                if(board[count][count2][0].colour != noToken)
                {
                    return board[count][0][count2].colour;
                }
            }
        }
    }

    // Checks for a mlin on the intersections between layers
    for(unsigned int count = 0; count < boardLayerWidth; count++)
    {
        for(unsigned int count2 = 0; count2 < boardLayerHeight; count2++)
        {
            if((board[0][count][count2].type == intersection) && (board[0][count][count2].colour != noToken))
            {
                if((board[0][count][count2].colour == board[1][count][count2].colour) && (board[0][count][count2].colour == board[2][count][count2].colour))
                {
                    return board[count][0][count2].colour;
                }
            }
        }
    }
    return noToken;
}

// After a mlin, this takes a piece if allowed.
bool gameData::takeToken(int xcoord, int ycoord, int laynum)
{
    enum posColour token = currentTurn;
    /*if(valPos(xcoord, ycoord, laynum) == 0)
    {
        return false;
    }*/
    if(board[laynum][xcoord][ycoord].mlinStatus > 0)
    {
        return false;
    }
    if(token == blackToken)
    {
        if(board[laynum][xcoord][ycoord].colour == whiteToken)
        {
            board[laynum][xcoord][ycoord].colour = noToken;
            board[laynum][xcoord][ycoord].locImg->setPixmap(*board[laynum][xcoord][ycoord].locImg->defaultImg);
            whitePieces.piecesOnBoard--;
            whitePieces.piecesTaken++;
            return true;
        }
    }
    else if(token == whiteToken)
    {
        if(board[laynum][xcoord][ycoord].colour == blackToken)
        {
            board[laynum][xcoord][ycoord].colour = noToken;
            blackPieces.piecesOnBoard--;
            blackPieces.piecesTaken++;
            board[laynum][xcoord][ycoord].locImg->setPixmap(*board[laynum][xcoord][ycoord].locImg->defaultImg);
            return true;
        }
    }
    return false;
}

// If a piece moves out of mlin, this function resets the mlinStatus of the appropriate positions
// It's possible that adjacent positions are in another mlin
// It's possible to move from one mlin into another, so this function must be used BEFORE checkForNewMlin()
void gameData::removeMlin(int xcoord, int ycoord, int laynum)
{
    if(board[laynum][xcoord][ycoord].mlinStatus == 0)
    {
        return;
    }
    else if(board[laynum][xcoord][ycoord].mlinStatus > 0)
    {
        if((board[laynum][xcoord][0].colour == board[laynum][xcoord][2].colour) && (board[laynum][xcoord][0].colour == board[laynum][xcoord][1].colour))
        {
            board[laynum][xcoord][0].mlinStatus--;
            board[laynum][xcoord][1].mlinStatus--;
            board[laynum][xcoord][2].mlinStatus--;
            if(board[laynum][xcoord][ycoord].colour == blackToken)
            {
                if(board[laynum][xcoord][0].mlinStatus == 0)
                    board[laynum][xcoord][0].locImg->setPixmap(*tokenImage.blackTokenMap);
                if(board[laynum][xcoord][1].mlinStatus == 0)
                    board[laynum][xcoord][1].locImg->setPixmap(*tokenImage.blackTokenMap);
                if(board[laynum][xcoord][2].mlinStatus == 0)
                    board[laynum][xcoord][2].locImg->setPixmap(*tokenImage.blackTokenMap);
            }
            else if(board[laynum][xcoord][ycoord].colour == whiteToken)
            {
                if(board[laynum][xcoord][0].mlinStatus == 0)
                    board[laynum][xcoord][0].locImg->setPixmap(*tokenImage.whiteTokenMap);
                if(board[laynum][xcoord][1].mlinStatus == 0)
                    board[laynum][xcoord][1].locImg->setPixmap(*tokenImage.whiteTokenMap);
                if(board[laynum][xcoord][2].mlinStatus == 0)
                    board[laynum][xcoord][2].locImg->setPixmap(*tokenImage.whiteTokenMap);
            }


        }
        if((board[laynum][0][ycoord].colour == board[laynum][2][ycoord].colour) && (board[laynum][0][ycoord].colour == board[laynum][1][ycoord].colour))
        {
            board[laynum][0][ycoord].mlinStatus--;
            board[laynum][1][ycoord].mlinStatus--;
            board[laynum][2][ycoord].mlinStatus--;
            if(board[laynum][xcoord][ycoord].colour == blackToken)
            {
                if(board[laynum][0][ycoord].mlinStatus == 0)
                     board[laynum][0][ycoord].locImg->setPixmap(*tokenImage.blackTokenMap);
                if(board[laynum][1][ycoord].mlinStatus == 0)
                    board[laynum][1][ycoord].locImg->setPixmap(*tokenImage.blackTokenMap);
                if(board[laynum][2][ycoord].mlinStatus == 0)
                  board[laynum][2][ycoord].locImg->setPixmap(*tokenImage.blackTokenMap);
            }
            else if(board[laynum][xcoord][ycoord].colour == whiteToken)
            {
                if(board[laynum][0][ycoord].mlinStatus == 0)
                    board[laynum][0][ycoord].locImg->setPixmap(*tokenImage.whiteTokenMap);
                if(board[laynum][1][ycoord].mlinStatus == 0)
                    board[laynum][1][ycoord].locImg->setPixmap(*tokenImage.whiteTokenMap);
                if(board[laynum][2][ycoord].mlinStatus == 0)
                  board[laynum][2][ycoord].locImg->setPixmap(*tokenImage.whiteTokenMap);
            }
        }
        if(board[laynum][xcoord][ycoord].type == intersection)
        {
                // Checks for a mlin across the layers
                if((board[0][xcoord][ycoord].colour == board[1][xcoord][ycoord].colour) && (board[1][xcoord][ycoord].colour == board[2][xcoord][ycoord].colour))
                {
                    board[0][xcoord][ycoord].mlinStatus--;
                    board[1][xcoord][ycoord].mlinStatus--;
                    board[2][xcoord][ycoord].mlinStatus--;
                    if(board[laynum][xcoord][ycoord].colour == blackToken)
                    {
                        if(board[0][xcoord][ycoord].mlinStatus == 0)
                            board[0][xcoord][ycoord].locImg->setPixmap(*tokenImage.blackTokenMap);
                        if(board[1][xcoord][ycoord].mlinStatus == 0)
                            board[1][xcoord][ycoord].locImg->setPixmap(*tokenImage.blackTokenMap);
                        if(board[2][xcoord][ycoord].mlinStatus == 0)
                            board[2][xcoord][ycoord].locImg->setPixmap(*tokenImage.blackTokenMap);
                    }
                    else if(board[laynum][xcoord][ycoord].colour == whiteToken)
                    {
                        if(board[0][xcoord][ycoord].mlinStatus == 0)
                            board[0][xcoord][ycoord].locImg->setPixmap(*tokenImage.whiteTokenMap);
                        if(board[1][xcoord][ycoord].mlinStatus == 0)
                            board[1][xcoord][ycoord].locImg->setPixmap(*tokenImage.whiteTokenMap);
                        if(board[2][xcoord][ycoord].mlinStatus == 0)
                            board[2][xcoord][ycoord].locImg->setPixmap(*tokenImage.whiteTokenMap);
                    }

                }
        }
    }
}

// The game is over if a player has less than three tokens left (after the placing stage)
// ... or if they can't move their pieces anywhere.
void gameData::checkForWin()
{
        if(whitePieces.piecesOnBoard + whitePieces.piecesUnplaced < 3)
        {
            gameStatus = blackWin;
            return;
        }
        else if(blackPieces.piecesOnBoard + whitePieces.piecesUnplaced < 3)
        {
            gameStatus = whiteWin;
            return;
        }

        /* These will become "true" if a white or black piece is next to an empty position */
        if(gameStatus == moving)
        {
            bool blackMove = false;
            bool whiteMove = false;
            for(unsigned int count = 0; count < numOfLayers; count++)
            {
                for(unsigned int count2 = 0; count2 < boardLayerHeight; count2++)
                {
                    for(unsigned int count3 = 0; count3 < boardLayerWidth; count3++)
                    {
                        if(checkForMove(count, count2, count3) == true)
                        {
                            if(board[count][count2][count3].colour == blackToken)
                                blackMove = true;
                            if(board[count][count2][count3].colour == whiteToken)
                                whiteMove = true;
                        }
                    }
                }
            }

            if(blackMove == false)
            {
                gameStatus = whiteWin;
                return;
            }
            else if(whiteMove == false)
            {
                gameStatus = blackWin;
                return;
            }
        }
        return;
}

// Checks to see if a piece can legally move
// This can be implemented to check for a win (a player loses if they can't move any piece)
// or to prevent a player from selecting a piece that cannot move in the move stage
//
bool gameData::checkForMove(unsigned int count, unsigned int count2, unsigned int count3)
{
    if((board[count][count2][count3].colour == blackToken) || (board[count][count2][count3].colour == whiteToken))
    {
        // If the position is a corner...
        if(board[count][count2][count3].type == corner)
        {
            if((board[count][1][count3].colour == noToken) || (board[count][count2][1].colour == noToken))
            {
                if(board[count][count2][count3].colour == blackToken)
                {
                    return true;
                }
                if(board[count][count2][count3].colour == whiteToken)
                {
                    return true;
                }
            }
        }

        // If the position is an intersection
        else if(board[count][count2][count3].type == intersection)
        {
            // If "count2" is 0 or 2, then "count3" must equal 1.
            if((count2 == 0) || (count2 == 2))
            {
                if((board[count][count2][0].colour == noToken) || (board[count][count2][2].colour == noToken))
                {
                    if(board[count][count2][count3].colour == blackToken)
                    {
                        return true;
                    }
                    if(board[count][count2][count3].colour == whiteToken)
                    {
                        return true;
                    }
                }
            }
            if((count3 == 0) || (count3 == 2))
            {
                if((board[count][0][count3].colour == noToken) || (board[count][2][count3].colour == noToken))
                {
                    if(board[count][count2][count3].colour == blackToken)
                    {
                        return true;
                    }
                    if(board[count][count2][count3].colour == whiteToken)
                    {

                        return true;
                    }
                }
            }
            if(count == 1)
            {
                if((board[0][count2][count3].colour == noToken) || (board[2][count2][count3].colour == noToken))
                {
                    if(board[count][count2][count3].colour == blackToken)
                    {
                        return true;
                    }
                    if(board[count][count2][count3].colour == whiteToken)
                    {

                        return true;
                    }
                }
            }
            else if((count == 0) || (count == 2))
            {
                if(board[1][count2][count3].colour == noToken)
                {
                    if(board[count][count2][count3].colour == blackToken)
                    {
                        return true;
                    }
                    if(board[count][count2][count3].colour == whiteToken)
                    {

                        return true;
                    }
                }
            }
        }

    }
    return false;
}

// This checks the entire board to see if the opponent has at least one piece which is able to be taken.
bool gameData::checkForTakableToken()
{
    enum posColour testingColour;
    if(currentTurn == blackToken)
    {
        testingColour = whiteToken;
    }
    else if(currentTurn == whiteToken)
    {
        testingColour = blackToken;
    }
    else
    {
        std::cout << "Error" << std::endl;
        return false;
    }
    for(unsigned int count = 0; count < numOfLayers; count++)
    {
        for(unsigned int count2 = 0; count2 < boardLayerHeight; count2++)
        {
            for(unsigned int count3 = 0; count3 < boardLayerWidth; count3++)
            {
                if((board[count][count2][count3].colour == testingColour) && (board[count][count2][count3].mlinStatus < 1))
                {
                    return true;
                }

            }
        }
    }
    return false;
}

void gameData::changeTurns()
{
    if(currentTurn == blackToken)
    {
        currentTurn = whiteToken;
    }
    else if(currentTurn == whiteToken)
    {
        currentTurn = blackToken;
    }
    selectedToken = noToken;
    if(((gameStatus == placing) && (blackPieces.piecesUnplaced <= 0) && (whitePieces.piecesUnplaced <= 0)))
    {
        gameStatus = moving;
    }
    checkForWin();
}

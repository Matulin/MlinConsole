#include "game.h"


void initGame(struct gameData * gameData)
{
    initBoard(gameData->board);
    gameData->gameStatus = placing;
    gameData->blackPieces.piecesOnBoard = 0;
    gameData->blackPieces.piecesUnplaced = numPieces;
    gameData->blackPieces.piecesTaken = 0;
    gameData->whitePieces.piecesOnBoard = 0;
    gameData->whitePieces.piecesUnplaced = numPieces;
    gameData->whitePieces.piecesTaken = 0;
}

bool valMove(struct position board[numOfLayers][boardLayerHeight][boardLayerWidth], int oldx, int oldy, int oldlay, int newx, int newy, int newlay)
{
    // Confirms that both positions exist.
    if(valPos(board, oldx, oldy, oldlay) == false)
    {
        return false;
    }
    if(valPos(board, newx, newy, newlay) == false)
    {
        return false;
    }

    // Confirms that neither position is an invalid position (i.e. the centre of a layer)
    if((board[oldlay-1][oldx - 1][oldy - 1].type == centre) || (board[newlay-1][newx - 1][newy - 1].type == centre))
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
        if(board[oldlay - 1][oldx - 1][oldy - 1].type == intersection)
        {
            if((newlay - oldlay == 1) || (newlay - oldlay == -1))
            {
                return true;
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
    // It's imposible for the old and new positions to be diagonal, since valPos has already checked for the centre of the layer
    if((newx - oldx >= -1) && (newx - oldx <= 1))
    {
        if((newy - oldy >= -1) && (newy - oldy <= 1))
        {
            return true;
        }
    }

    cout << "There was an error validating the move!" << endl;
    return false;
}

bool placePiece(struct gameData * data, int xcoord, int ycoord, int lay, enum posColour newToken)
{
    if(data->blackPieces.piecesUnplaced <= 0)
    {
        return false;
    }
    if(valPos(data->board, xcoord, ycoord, lay) == false)
    {
        return false;
    }
    data->board[lay][xcoord][ycoord].colour = newToken;
    if(newToken == blackToken)
    {
        data->blackPieces.piecesOnBoard++;
        data->blackPieces.piecesUnplaced--;
        return true;
    }
    else if(newToken == whiteToken)
    {
        data->whitePieces.piecesOnBoard++;
        data->whitePieces.piecesUnplaced--;
        return true;
    }
    return false;
}

// When all the tokens have been placed, each player takes turns moving a piece one position.
// Attempting to move a token outside the size of the array from a middle-position will result in moving the piece to the next layer.
// A player cannot of course move outwards from the outer-most layer, or inwards from the inner-most layer.
// It is also impossible to move between layers from the corners of a layer.
bool moveToken(struct gameData * data, int oldx, int oldy, int oldlay, int newx, int newy, int newlay, enum posColour newToken)
{

    if(valMove(data->board, oldx, oldy, oldlay, newx, newy, newlay) != true)
    {
        return false;
    }


    data->board[oldlay - 1][oldx - 1][oldy - 1].colour = noToken;
    data->board[newlay - 1][newx - 1][newy - 1].colour = newToken;
    return true;
}
int checkForNewMlin(struct gameData * data, int xcoord, int ycoord, int laynum, enum posColour newToken)
{
    int mlin = 0; // It's possible for a single move to make 0, 1 or 2 mlins.
    // If the new position is a corner...
    if(data->board[laynum][xcoord][ycoord].type == corner)
    {
        unsigned int adjx;
        unsigned int adjy;
        if(xcoord == 0)
        {
            adjx = 2;
        }
        else if(xcoord == 2)
        {
            adjx = 0;
        }

        if(ycoord == 0)
        {
            adjy = 2;
        }
        else if(ycoord == 2)
        {
            adjy = 0;
        }
        if((data->board[laynum][xcoord][ycoord].colour == data->board[laynum][xcoord][adjy].colour) && (data->board[laynum][xcoord][ycoord].colour == data->board[laynum][xcoord][1].colour))
        {
            data->board[laynum][xcoord][ycoord].mlinStatus++;
            data->board[laynum][xcoord][adjy].mlinStatus++;
            data->board[laynum][xcoord][1].mlinStatus++;
            mlin++;
        }

        if((data->board[laynum][xcoord][ycoord].colour == data->board[laynum][adjx][ycoord].colour) && (data->board[laynum][xcoord][ycoord].colour == data->board[laynum][1][ycoord].colour))
        {
            data->board[laynum][xcoord][ycoord].mlinStatus++;
            data->board[laynum][adjx][ycoord].mlinStatus++;
            data->board[laynum][1][ycoord].mlinStatus++;
            mlin++;

        }
    }

    // If the new position is an intersection
    else if(data->board[laynum][xcoord][ycoord].type == intersection)
    {
        if(xcoord == 1)
        {
            if((data->board[laynum][xcoord][ycoord].colour == data->board[laynum][xcoord][ycoord + 1].colour) && (data->board[laynum][xcoord][ycoord].colour == data->board[laynum][xcoord][ycoord - 1].colour))
            {
                data->board[laynum][xcoord][ycoord].mlinStatus++;
                data->board[laynum][xcoord][ycoord + 1].mlinStatus++;
                data->board[laynum][xcoord][ycoord - 1].mlinStatus++;
                mlin++;
            }
        }

        else if(ycoord == 1)
        {
            if((data->board[laynum][xcoord][ycoord].colour == data->board[laynum][xcoord + 1][ycoord].colour) && (data->board[laynum][xcoord][ycoord].colour == data->board[laynum][xcoord - 1][ycoord].colour))
            {
                data->board[laynum][xcoord][ycoord].mlinStatus++;
                data->board[laynum][xcoord + 1][ycoord].mlinStatus++;
                data->board[laynum][xcoord - 1][ycoord].mlinStatus++;
                mlin++;
            }
        }
        if((data->board[0][xcoord][ycoord].colour == data->board[1][xcoord][ycoord].colour) && (data->board[laynum][xcoord][ycoord].colour == data->board[2][xcoord][ycoord].colour))
        {
            data->board[laynum][xcoord][ycoord].mlinStatus++;
            data->board[laynum][xcoord][ycoord].mlinStatus++;
            data->board[laynum][xcoord][ycoord].mlinStatus++;
            mlin++;
        }
    }
    return mlin;
}

// First, this checks if there are any three tokens of the same type lined up. If so, that player gets a "mlin" and can choose to take a piece.
// If a player cannot move any pieces anywhere, or they have less than two pieces left on the board (after having placed all their pieces), they lose the game.
enum posColour checkForMlin(struct position board[numOfLayers][boardLayerHeight][boardLayerWidth])
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
}

// After a mlin, this takes a piece if allowed.
bool takeToken(struct gameData * data, int xcoord, int ycoord, int laynum, enum posColour token)
{
    if(valPos(data->board, xcoord, ycoord, laynum) == 0)
    {
        return false;
    }
    if(data->board[laynum][xcoord][ycoord].mlinStatus > 0)
    {
        return false;
    }
    if(token == blackToken)
    {
        if(data->board[laynum][xcoord][ycoord].colour == whiteToken)
        {
            data->board[laynum][xcoord][ycoord].colour = noToken;
            data->whitePieces.piecesOnBoard--;
            data->whitePieces.piecesTaken++;
            return true;
        }
    }
    else if(token == whiteToken)
    {
        if(data->board[laynum][xcoord][ycoord].colour == blackToken)
        {
            data->board[laynum][xcoord][ycoord].colour = noToken;
            data->blackPieces.piecesOnBoard--;
            data->blackPieces.piecesTaken++;
            return true;
        }
    }
    return false;
}

// If a piece moves out of mlin, this function resets the mlinStatus of the appropriate positions
// It's possible that adjacent positions are in another mlin
// It's possible to move from one mlin into another, so this function must be used BEFORE checkForNewMlin()
void removeMlin(struct gameData * data, int xcoord, int ycoord, int laynum)
{
    if(data->board[laynum][xcoord][ycoord].mlinStatus == 0)
    {
        return;
    }
    else if(data->board[laynum][xcoord][ycoord].mlinStatus > 0)
    {
        data->board[laynum][xcoord][ycoord].mlinStatus--;
        if(data->board[laynum][xcoord][ycoord].type == corner)
        {
            unsigned int adjx;
            unsigned int adjy;
            if(xcoord = 0)
            {
                adjx = 2;
            }
            else if(xcoord = 2)
            {
                adjx = 0;
            }

            if(ycoord = 0)
            {
                adjy = 2;
            }
            else if(ycoord = 2)
            {
                adjy = 0;
            }
            if(data->board[laynum][xcoord][1].mlinStatus > 0)
            {
                data->board[laynum][xcoord][1].mlinStatus--;
                data->board[laynum][xcoord][adjy].mlinStatus--;
            }
            else if(data->board[laynum][1][ycoord].mlinStatus > 0)
            {
                data->board[laynum][1][ycoord].mlinStatus--;
                data->board[laynum][adjx][ycoord].mlinStatus--;
            }
        }

        if(data->board[laynum][xcoord][ycoord].type == intersection)
        {
            if(xcoord == 1)
            {
                if((data->board[laynum][0][ycoord].mlinStatus > 0) && (data->board[laynum][2][ycoord].mlinStatus > 0))
                {
                    data->board[laynum][0][ycoord].mlinStatus--;
                    data->board[laynum][2][ycoord].mlinStatus--;
                }
            }

            if(ycoord == 1)
            {
                if((data->board[laynum][xcoord][0].mlinStatus > 0) && (data->board[laynum][xcoord][2].mlinStatus > 0))
                {
                    data->board[laynum][xcoord][0].mlinStatus--;
                    data->board[laynum][xcoord][2].mlinStatus--;
                }
            }

            if(laynum == 0)
            {
                if((data->board[1][xcoord][ycoord].mlinStatus > 0) && (data->board[2][xcoord][ycoord].mlinStatus > 0))
                {
                    data->board[1][xcoord][ycoord].mlinStatus--;
                    data->board[2][xcoord][ycoord].mlinStatus--;
                }
            }

            if(laynum == 1)
            {
                if((data->board[0][xcoord][ycoord].mlinStatus > 0) && (data->board[2][xcoord][ycoord].mlinStatus > 0))
                {
                    data->board[0][xcoord][ycoord].mlinStatus--;
                    data->board[2][xcoord][ycoord].mlinStatus--;
                }
            }

            if(laynum == 2)
            {
                if((data->board[1][xcoord][ycoord].mlinStatus > 0) && (data->board[0][xcoord][ycoord].mlinStatus > 0))
                {
                    data->board[1][xcoord][ycoord].mlinStatus--;
                    data->board[0][xcoord][ycoord].mlinStatus--;
                }
            }

        }
    }
}

// The game is over if a player has less than three tokens left (after the placing stage)
// ... or if they can't move their pieces anywhere.
void checkForWin(struct gameData * data)
{
    if(data->gameStatus == moving)
    {
        if(data->whitePieces.piecesOnBoard < 3)
        {
            data->gameStatus = blackWin;
            return;
        }
        else if(data->blackPieces.piecesOnBoard < 3)
        {
            data->gameStatus = whiteWin;
            return;
        }

        /* These will become "true" if a white or black piece is next to an empty position */
        bool blackMove = false;
        bool whiteMove = false;
        for(unsigned int count = 0; count < numOfLayers; count++)
        {
            for(unsigned int count2 = 0; count2 < boardLayerHeight; count2++)
            {
                for(unsigned int count3 = 0; count3 < boardLayerWidth; count3++)
                {
                    if((data->board[count][count2][count3].colour == blackToken) || (data->board[count][count2][count3].colour == whiteToken))
                    {
                        // If the position is a corner...
                        if(data->board[count][count2][count3].type == corner)
                        {
                            if((data->board[count][1][count3].colour != noToken) || (data->board[count][count2][1].colour != noToken))
                            {
                                if(data->board[count][count2][count3].colour == blackToken)
                                {
                                    blackMove = true;
                                }
                                if(data->board[count][count2][count3].colour == whiteToken)
                                {
                                    whiteMove = true;
                                }
                            }
                        }

                        // If the position is an intersection
                        else if(data->board[count][count2][count3].type == intersection)
                        {
                            if((count2 == 0) || (count2 == 2))
                            {
                                if((data->board[count][count2][0].colour == noToken) || (data->board[count][count2][2].colour == noToken))
                                {
                                    if(data->board[count][count2][count3].colour == blackToken)
                                    {
                                        blackMove = true;
                                    }
                                    if(data->board[count][count2][count3].colour == whiteToken)
                                    {
                                        whiteMove = true;
                                    }
                                }
                            }
                            if((count3 == 0) || (count3 == 2))
                            {
                                if((data->board[count][0][count3].colour == noToken) || (data->board[count][2][count3].colour == noToken))
                                {
                                    if(data->board[count][count2][count3].colour == blackToken)
                                    {
                                        blackMove = true;
                                    }
                                    if(data->board[count][count2][count3].colour == whiteToken)
                                    {
                                        whiteMove = true;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        if(blackMove == false)
        {
            data->gameStatus = whiteWin;
            return;
        }
        else if(whiteMove == false)
        {
            data->gameStatus = blackWin;
            return;
        }
        return;
    }
    else
    {
        return;
    }
}

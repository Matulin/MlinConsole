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
    }
    else if(newToken == whiteToken)
    {
        data->whitePieces.piecesOnBoard++;
        data->whitePieces.piecesUnplaced--;
    }
    if((data->whitePieces.piecesUnplaced == 0) && (data->blackPieces.piecesUnplaced == 0))
    {
        data->gameStatus = moving;
    }
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
        if((data->board[laynum][xcoord][ycoord].colour == data->board[laynum][xcoord][adjy].colour) && (data->board[laynum][xcoord][ycoord].colour == data->board[laynum][xcoord][1].colour))
        {
            data->board[laynum][xcoord][ycoord].mlinStatus = true;
            data->board[laynum][xcoord][adjy].mlinStatus = true;
            data->board[laynum][xcoord][1].mlinStatus = true;
            mlin++;
        }

        if((data->board[laynum][xcoord][ycoord].colour == data->board[laynum][adjx][ycoord].colour) && (data->board[laynum][xcoord][ycoord].colour == data->board[laynum][1][ycoord].colour))
        {
            data->board[laynum][xcoord][ycoord].mlinStatus = true;
            data->board[laynum][adjx][ycoord].mlinStatus = true;
            data->board[laynum][1][ycoord].mlinStatus = true;
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
                data->board[laynum][xcoord][ycoord].mlinStatus = true;
                data->board[laynum][xcoord][ycoord + 1].mlinStatus = true;
                data->board[laynum][xcoord][ycoord - 1].mlinStatus = true;
                mlin++;
            }
        }

        else if(ycoord == 1)
        {
            if((data->board[laynum][xcoord][ycoord].colour == data->board[laynum][xcoord + 1][ycoord].colour) && (data->board[laynum][xcoord][ycoord].colour == data->board[laynum][xcoord - 1][ycoord].colour))
            {
                data->board[laynum][xcoord][ycoord].mlinStatus = true;
                data->board[laynum][xcoord + 1][ycoord].mlinStatus = true;
                data->board[laynum][xcoord - 1][ycoord].mlinStatus = true;
                mlin++;
            }
        }
        if((data->board[0][xcoord][ycoord].colour == data->board[1][xcoord][ycoord].colour) && (data->board[laynum][xcoord][ycoord].colour == data->board[2][xcoord][ycoord].colour))
        {
            data->board[laynum][xcoord][ycoord].mlinStatus = true;
            data->board[laynum][xcoord][ycoord].mlinStatus = true;
            data->board[laynum][xcoord][ycoord].mlinStatus = true;
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

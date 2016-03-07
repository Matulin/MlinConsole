#include "board.h"

// Initalises the board
// Each layer has 9 positions: 8 which will start out as empty, and 1 invalid one in the middle of each layer
bool initBoard(struct position board[numOfLayers][boardLayerHeight][boardLayerWidth])
{
    // For each layer...
    for(unsigned int count = 0; count < numOfLayers; count++)
    {
        // For every position in the layer...
        for(unsigned int count2 = 0; count2 < boardLayerHeight; count2++)
        {
            for(unsigned int count3 = 0; count3 < boardLayerWidth; count3++)
            {
                // If the position is not in the centre of the layer...
                if(!((count2 % 2 == 1) && (count3 % 2 == 1)))
                {

                    // If the position is an intersection...
                    if((count2 % 2 == 1) || (count3 % 2 == 1))
                    {
                        board[count][count2][count3].colour = noToken;
                        board[count][count2][count3].type = intersection;
                        board[count][count2][count3].mlinStatus = 0;
                    }

                    // If the position is a corner...
                    else if((count2 % 2 != 1) && (count3 % 2 != 1))
                    {
                        board[count][count2][count3].colour = noToken;
                        board[count][count2][count3].type = corner;
                        board[count][count2][count3].mlinStatus = 0;
                    }
                    else
                    {
                        cout << "There was an error initialising the board - #1" << endl;
                        return false;
                    }
                }

                // If the position is at the centre of the layer...
                else if((count2 % 2 == 1) && (count3 % 2 == 1))
                {
                    board[count][count2][count3].colour = invalidToken;
                    board[count][count2][count3].type = centre;
                    board[count][count2][count3].mlinStatus = 0;
                }
                else
                {
                    cout << "There was an error initialising the board - #2" << endl;
                    cout << "count: " << count << endl;
                    cout << "count2: " << count2 << endl;
                    cout << "count3: " << count3 << endl;
                    return false;
                }
            }
        }
    }
    return true;
}

void initGame(struct gameData * gameData)
{
    initBoard(gameData->board);
    gameData->gameStatus = placing;
    gameData->whiteMlins = 0;
    gameData->blackMlins = 0;
    gameData->blackPieces.piecesOnBoard = 0;
    gameData->blackPieces.piecesUnplaced = numPieces;
    gameData->blackPieces.piecesTaken = 0;
    gameData->whitePieces.piecesOnBoard = 0;
    gameData->whitePieces.piecesUnplaced = numPieces;
    gameData->whitePieces.piecesTaken = 0;
}

// Validates that a position is a valid position on the board, and that it has no token on it.
bool valPos(struct position board[numOfLayers][boardLayerHeight][boardLayerWidth], int xcoord, int ycoord, int layerNum)
{
    if((0 > xcoord) || (boardLayerHeight <= xcoord))
    {
        return false;
    }

    if((0 > ycoord) || (boardLayerWidth <= ycoord))
    {
        return false;
    }

    if((0 > layerNum) || (numOfLayers <= layerNum))
    {
        return false;
    }

    if(board[layerNum][xcoord][ycoord].colour != noToken)
    {
        return false;
    }
    return true;
}

// Validates that two coordinates are next to each other on the board.
// This n
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


// Displays the Board
void displayBoard(struct position board[numOfLayers][boardLayerHeight][boardLayerWidth])
{
    // This is just a placeholder to test that the board initialised correctly
        // For each layer...
    for(unsigned int count = 0; count < numOfLayers; count++)
    {
        cout << "Layer Number: " << count << endl;
        // For every position in the layer...
        for(unsigned int count2 = 0; count2 < boardLayerHeight; count2++)
        {
            for(unsigned int count3 = 0; count3 < boardLayerWidth; count3++)
            {
                cout << board[count][count2][count3].colour;
            }
            cout << endl;
        }
    }
}

// The first stage of the game. Each player starts with 9 tokens of an appropriate colour.
// A token may be placed on any empty square.
bool placePiece(struct position board[numOfLayers][boardLayerHeight][boardLayerWidth], int xcoord, int ycoord, int lay, enum posColour newToken)
{
    if(valPos(board, xcoord, ycoord, lay) == false)
    {
        return false;
    }
    board[lay][xcoord][ycoord].colour = newToken;
    return true;
}

// When all the tokens have been placed, each player takes turns moving a piece one position.
// Attempting to move a token outside the size of the array from a middle-position will result in moving the piece to the next layer.
// A player cannot of course move outwards from the outer-most layer, or inwards from the inner-most layer.
// It is also impossible to move between layers from the corners of a layer.
bool moveToken(struct position board[numOfLayers][boardLayerHeight][boardLayerWidth], int oldx, int oldy, int oldlay, int newx, int newy, int newlay, enum posColour newToken)
{


    if(valMove(board, oldx, oldy, oldlay, newx, newy, newlay) != true)
    {
        return false;
    }


    board[oldlay - 1][oldx - 1][oldy - 1].colour = noToken;
    board[newlay - 1][newx - 1][newy - 1].colour = newToken;
    return true;
}

bool checkForNewMlin(struct position board[numOfLayers][boardLayerHeight][boardLayerWidth], int xcoord, int ycoor, int laynum)
{

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

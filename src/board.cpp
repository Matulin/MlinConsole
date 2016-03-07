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
// This nstruct gameData * gameData


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


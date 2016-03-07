#include "board.h"

// Initalises the board
// Each layer has 9 positions: 8 which will start out as empty, and 1 invalid one in the middle of each layer
bool initBoard(boardLayer * totalBoard)
{
    // For each layer...
    for(unsigned int count = 0; count < numOfLayers; count++)
    {
        boardLayer thisLayer;
        // For every position in the layer...
        for(unsigned int count2 = 0; count2 < boardLayerHeight; count2++)
        {
            for(unsigned int count3 = 0; count3 < boardLayerWidth; count3++)
            {
                // If the position is not in the centre of the layer...
                if((count2 % 2 != 1) && (count3 % 2 != 1))
                {
                    thisLayer[count2][count3].colour = noToken;

                    // If the position is an intercection...
                    if((count2 % 2 == 1) || (count3 % 2 == 1))
                    {
                        thisLayer[count2][count3].colour = noToken;
                        thisLayer[count2][count3].type = intersection;
                    }

                    // If the position is a corner...
                    else if((count2 % 2 != 1) && (count3 % 2 != 1))
                    {
                        thisLayer[count2][count3].colour = noToken;
                        thisLayer[count2][count3].type = corner;
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
                    thisLayer[count2][count3].colour = invalidToken;
                    thisLayer[count2][count3].type = centre;
                }
                else
                {
                    cout << "There was an error initialising the board - #2" << endl;
                    return false;
                }
            }
        }

        // Assigns the newly-made layer to totalBoard
        (totalBoard + count) = thisLayer;
    }
    return true;
}

// Displays the Board
void displayBoard()
{

}

// The first stage of the game. Each player starts with 9 tokens of an appropriate colour.
// A token may be placed on any empty square.
void placePiece()
{

}

// When all the tokens have been placed, each player takes turns moving a piece one position.
// Attempting to move a token outside the size of the array from a middle-position will result in moving the piece to the next layer.
// A player cannot of course move outwards from the outer-most layer, or inwards from the inner-most layer.
// It is also impossible to move between layers from the corners of a layer.
void moveToken()
{

}

// First, this checks if there are any three tokens of the same type lined up. If so, that player wins.
// If a player cannot move any pieces anywhere, they lose the game.
void checkResult()
{

}

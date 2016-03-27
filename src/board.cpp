#include "board.h"

// Initalises the board
// Each layer has 9 positions: 8 which will start out as empty, and 1 invalid one in the middle of each layer
bool gameData::initBoard()
{
    /*struct position board[numOfLayers][boardLayerHeight][boardLayerWidth];*/
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
                        board[count][count2][count3].locImg = new QLabel;

                    }

                    // If the position is a corner...
                    else if((count2 % 2 != 1) && (count3 % 2 != 1))
                    {
                        board[count][count2][count3].colour = noToken;
                        board[count][count2][count3].type = corner;
                        board[count][count2][count3].mlinStatus = 0;
                        board[count][count2][count3].locImg = new QLabel;

                    }

                    int neg;
                    if(count2 == 0)
                    {
                        neg = 1;
                    }
                    else if (count2 == 1)
                    {
                        neg = 0;
                    }
                    else
                    {
                        neg = -1;
                    }

                    board[count][count2][count3].xCoordWidget = neg * count * 2 + 7 * count2;

                    int neg2;
                    if(count3 == 0)
                    {
                        neg2 = 1;
                    }
                    else if (count3 == 1)
                    {
                        neg2 = 0;
                    }
                    else
                    {
                        neg2 = -1;
                    }

                    board[count][count2][count3].yCoordWidget = neg2 * count * 2 + 6 * count3;



                }

                // If the position is at the centre of the layer...
                else if((count2 % 2 == 1) && (count3 % 2 == 1))
                {
                    board[count][count2][count3].colour = invalidToken;
                    board[count][count2][count3].type = centre;
                    board[count][count2][count3].mlinStatus = 0;
                    board[count][count2][count3].locImg = new QLabel;

                    board[count][count2][count3].xCoordWidget = -1;
                    board[count][count2][count3].yCoordWidget = -1;
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



bool gameData::initBoardWidget()
{

    boardWidget = new QWidget;
    QGridLayout * boardGrid = new QGridLayout;
    boardWidget->setLayout(boardGrid);

    for(unsigned int count = 0; count <= boardWidgetHeight; count++)
    {
        for(unsigned int count2 = 0; count2 <= boardWidgetWidth; count2++)
        {
            QLabel * tempLabel = new QLabel;
            tempLabel->setPixmap(*(tokenImage.emptyTokenMap));
            boardGrid->addWidget(tempLabel, count, count2);
        }
    }

    for(unsigned int count = 0; count < numOfLayers; count++)
    {

        for(unsigned int count2 = 0; count2 < boardLayerHeight; count2++)
        {
            for(unsigned int count3 = 0; count3 < boardLayerWidth; count3++)
            {
                board[count][count2][count3].locImg->setPixmap(*(tokenImage.blackTokenMap));
                std::cout << board[count][count2][count3].xCoordWidget << endl;
                if(board[count][count2][count3].xCoordWidget >= 0)
                {
                    boardGrid->addWidget(board[count][count2][count3].locImg, board[count][count2][count3].xCoordWidget, board[count][count2][count3].yCoordWidget);
                }
            }
        }
    }

    return true;
}

// Validates that a position is a valid position on the board, and that it has no token on it.
bool gameData::valPos(int xcoord, int ycoord, int layerNum)
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


// Displays the board in the command line for the purposes of testing.
// This will eventually be displayed by a GUI.
void gameData::displayBoard()
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


#include <graphics.h>

squareGraphic::squareGraphic(QLabel *parent)
    : QLabel(parent)
{

    connect(this, SIGNAL(clicked()), this, SLOT(functionTest()));
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

    std::cout << "Test" << std::endl;
    emit clicked();
}

void squareGraphic::functionTest()
{
    std::cout << "Layer: " << arrayLayNum << "X: " << arrayXCoord << "Y: " << arrayYCoord << std::endl;
}

#include "toolbar.h"


gameToolbar::gameToolbar(QWidget *parent)
    : QWidget(parent)
{
    gameMenu = new QMenu;
    toolbarLayout = new QHBoxLayout;
    gameMenu->addMenu(tr("&Game"));

    restartButton = new QAction(tr("&Restart Game"), this);
    restartButton->setStatusTip(tr("Restart this game"));
    gameMenu->addAction(restartButton);

    saveButton = new QAction(tr("&Save"), this);
    saveButton->setStatusTip(tr("Save this game"));
    gameMenu->addAction(saveButton);

    toolbarLayout->addWidget(gameMenu);
    setLayout(toolbarLayout);
}

gameToolbar::~gameToolbar()
{

}

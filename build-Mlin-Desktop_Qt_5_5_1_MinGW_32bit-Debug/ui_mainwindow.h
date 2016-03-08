/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QFrame *Layer1top;
    QFrame *Layer1bottom;
    QFrame *Layer1left;
    QFrame *Layer1right;
    QFrame *Layer2top;
    QFrame *Layer2bottom;
    QFrame *Layer2left;
    QFrame *Layer2right;
    QFrame *Layer3top;
    QFrame *Layer3bottom;
    QFrame *Layer3left;
    QFrame *Layer3right;
    QFrame *Intersectiontop;
    QFrame *Intersectionbottom;
    QFrame *Intersectionleft;
    QFrame *Intersectionright;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(500, 600);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        Layer1top = new QFrame(centralWidget);
        Layer1top->setObjectName(QStringLiteral("Layer1top"));
        Layer1top->setGeometry(QRect(50, 30, 400, 2));
        Layer1top->setFrameShape(QFrame::HLine);
        Layer1top->setFrameShadow(QFrame::Sunken);
        Layer1bottom = new QFrame(centralWidget);
        Layer1bottom->setObjectName(QStringLiteral("Layer1bottom"));
        Layer1bottom->setGeometry(QRect(50, 570, 400, 2));
        Layer1bottom->setFrameShape(QFrame::HLine);
        Layer1bottom->setFrameShadow(QFrame::Sunken);
        Layer1left = new QFrame(centralWidget);
        Layer1left->setObjectName(QStringLiteral("Layer1left"));
        Layer1left->setGeometry(QRect(50, 30, 2, 540));
        Layer1left->setFrameShape(QFrame::VLine);
        Layer1left->setFrameShadow(QFrame::Sunken);
        Layer1right = new QFrame(centralWidget);
        Layer1right->setObjectName(QStringLiteral("Layer1right"));
        Layer1right->setGeometry(QRect(450, 30, 2, 540));
        Layer1right->setFrameShape(QFrame::VLine);
        Layer1right->setFrameShadow(QFrame::Sunken);
        Layer2top = new QFrame(centralWidget);
        Layer2top->setObjectName(QStringLiteral("Layer2top"));
        Layer2top->setGeometry(QRect(110, 85, 280, 2));
        Layer2top->setFrameShape(QFrame::HLine);
        Layer2top->setFrameShadow(QFrame::Sunken);
        Layer2bottom = new QFrame(centralWidget);
        Layer2bottom->setObjectName(QStringLiteral("Layer2bottom"));
        Layer2bottom->setGeometry(QRect(110, 515, 280, 2));
        Layer2bottom->setFrameShape(QFrame::HLine);
        Layer2bottom->setFrameShadow(QFrame::Sunken);
        Layer2left = new QFrame(centralWidget);
        Layer2left->setObjectName(QStringLiteral("Layer2left"));
        Layer2left->setGeometry(QRect(110, 85, 2, 430));
        Layer2left->setFrameShape(QFrame::VLine);
        Layer2left->setFrameShadow(QFrame::Sunken);
        Layer2right = new QFrame(centralWidget);
        Layer2right->setObjectName(QStringLiteral("Layer2right"));
        Layer2right->setGeometry(QRect(390, 85, 2, 430));
        Layer2right->setFrameShape(QFrame::VLine);
        Layer2right->setFrameShadow(QFrame::Sunken);
        Layer3top = new QFrame(centralWidget);
        Layer3top->setObjectName(QStringLiteral("Layer3top"));
        Layer3top->setGeometry(QRect(170, 140, 160, 2));
        Layer3top->setFrameShape(QFrame::HLine);
        Layer3top->setFrameShadow(QFrame::Sunken);
        Layer3bottom = new QFrame(centralWidget);
        Layer3bottom->setObjectName(QStringLiteral("Layer3bottom"));
        Layer3bottom->setGeometry(QRect(170, 460, 160, 2));
        Layer3bottom->setFrameShape(QFrame::HLine);
        Layer3bottom->setFrameShadow(QFrame::Sunken);
        Layer3left = new QFrame(centralWidget);
        Layer3left->setObjectName(QStringLiteral("Layer3left"));
        Layer3left->setGeometry(QRect(170, 140, 2, 320));
        Layer3left->setFrameShape(QFrame::VLine);
        Layer3left->setFrameShadow(QFrame::Sunken);
        Layer3right = new QFrame(centralWidget);
        Layer3right->setObjectName(QStringLiteral("Layer3right"));
        Layer3right->setGeometry(QRect(330, 140, 2, 320));
        Layer3right->setFrameShape(QFrame::VLine);
        Layer3right->setFrameShadow(QFrame::Sunken);
        Intersectiontop = new QFrame(centralWidget);
        Intersectiontop->setObjectName(QStringLiteral("Intersectiontop"));
        Intersectiontop->setGeometry(QRect(250, 30, 2, 110));
        Intersectiontop->setFrameShape(QFrame::VLine);
        Intersectiontop->setFrameShadow(QFrame::Sunken);
        Intersectionbottom = new QFrame(centralWidget);
        Intersectionbottom->setObjectName(QStringLiteral("Intersectionbottom"));
        Intersectionbottom->setGeometry(QRect(250, 460, 2, 110));
        Intersectionbottom->setFrameShape(QFrame::VLine);
        Intersectionbottom->setFrameShadow(QFrame::Sunken);
        Intersectionleft = new QFrame(centralWidget);
        Intersectionleft->setObjectName(QStringLiteral("Intersectionleft"));
        Intersectionleft->setGeometry(QRect(50, 320, 120, 2));
        Intersectionleft->setFrameShape(QFrame::HLine);
        Intersectionleft->setFrameShadow(QFrame::Sunken);
        Intersectionright = new QFrame(centralWidget);
        Intersectionright->setObjectName(QStringLiteral("Intersectionright"));
        Intersectionright->setGeometry(QRect(330, 320, 120, 2));
        Intersectionright->setFrameShape(QFrame::HLine);
        Intersectionright->setFrameShadow(QFrame::Sunken);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 500, 26));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

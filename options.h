#ifndef OPTIONS_H
#define OPTIONS_H


#include <QApplication>
#include <QtGui>
#include <QDialog>
#include <board.h>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QString>
#include <QFile>
#include <QIODevice>
#include <QXmlStreamWriter>
#include <QRegExp>


class QApplication;
class gameData;

class optionFunctions : public QWidget
{
   Q_OBJECT
public:
    explicit optionFunctions(gameData * gameData, QApplication * thisApp);
public:
    QApplication * runningApp;
    gameData * thisGameData;

public slots:
    void exitApp();
    void restartGame();
    void saveGame();
};

class saveDialog : public QDialog
{
    Q_OBJECT

public:
    explicit saveDialog();

public:
    QPushButton * saveButton;
    QPushButton * cancelButton;
    QLabel * saveLabel;
    QLineEdit * inputText;
    QString inputTextString;

public slots:
    void createFile();
    void recordInputText(const QString input);
    void closeDialog();
};

#endif // OPTIONS_H

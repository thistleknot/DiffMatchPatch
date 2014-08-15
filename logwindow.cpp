#include "logwindow.h"
#include "ui_logwindow.h"

LogWindow::LogWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LogWindow)
{
    ui->setupUi(this);
}

LogWindow::~LogWindow()
{
    delete ui;
}

//needs to be LogWindow:: otherwise doesn't have access to other elements, derp!
//void readString (QString incomingString)
void LogWindow::readString (QString incomingString)
{
    incomingS = incomingString;
    ui->plainTextEditObjects->setPlainText(incomingS);
}

void LogWindow::readInt (int incomingInt)
{
    incomingI = incomingInt;

    QString incomingIS = QString::number(incomingI);

    ui->labelNumOfTags->setText(incomingIS);
}

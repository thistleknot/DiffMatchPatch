#ifndef LOGWINDOW_H
#define LOGWINDOW_H

#include <QMainWindow>

namespace Ui {
class LogWindow;
}

class LogWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LogWindow(QWidget *parent = 0);

    void readString (QString incomingString);

    void readInt (int incomingInt);

    ~LogWindow();

private:
    Ui::LogWindow *ui;

    QString incomingS;

    int incomingI;

};

#endif // LOGWINDOW_H

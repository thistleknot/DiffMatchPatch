#ifndef PATCHOUTPUTWINDOW_H
#define PATCHOUTPUTWINDOW_H

#include <QMainWindow>
#include <QObject>

namespace Ui {
class PatchOutputWindow;
}

class PatchOutputWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit PatchOutputWindow(QWidget *parent = 0);

    void setOutputWindowText(QString);

    ~PatchOutputWindow();

public slots:

    //void receiveData(QString object);

    //protected:

    //void closeEvent(QCloseEvent *event);

signals:

    //void sendData(QString);


private slots:
    void on_actionSave_triggered();

private:
    Ui::PatchOutputWindow *ui;
    QString m_value;
};

#endif // PATCHOUTPUTWINDOW_H

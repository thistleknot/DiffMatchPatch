#ifndef PATCHOUTPUTWINDOW_H
#define PATCHOUTPUTWINDOW_H

#include <QMainWindow>

namespace Ui {
class PatchOutputWindow;
}

class PatchOutputWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit PatchOutputWindow(QWidget *parent = 0);
    ~PatchOutputWindow();

    protected:

    //void closeEvent(QCloseEvent *event);


private:
    Ui::PatchOutputWindow *ui;
};

#endif // PATCHOUTPUTWINDOW_H

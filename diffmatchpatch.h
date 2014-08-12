#ifndef DIFFMATCHPATCH_H
#define DIFFMATCHPATCH_H

#include <QMainWindow>
#include <patchoutputwindow.h>

namespace Ui {
class DiffMatchPatch;
}

class DiffMatchPatch : public QMainWindow
{
    Q_OBJECT

public:
    explicit DiffMatchPatch(QWidget *parent = 0);
    ~DiffMatchPatch();

private slots:
    void on_actionOpen_Left_triggered();

    void on_actionOpen_Right_triggered();

    void on_actionSave_Left_triggered();

    void on_actionSave_Right_triggered();

    void on_actionPatch_Compute_triggered();

private:
    Ui::DiffMatchPatch *ui;
    //PatchOutputWindow *patchOutputWindow;
    PatchOutputWindow *mMyNewWindow;
};

#endif // DIFFMATCHPATCH_H

#ifndef DIFFMATCHPATCH_H
#define DIFFMATCHPATCH_H

#include <QMainWindow>
#include <QObject>

#include <diff_match_patch.h>

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

    //Ui::PatchOutputWindow *uiOutput;
};

#endif // DIFFMATCHPATCH_H

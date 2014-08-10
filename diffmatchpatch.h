#ifndef DIFFMATCHPATCH_H
#define DIFFMATCHPATCH_H

#include <QMainWindow>

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

    void on_actionCompute_Patch_triggered();

private:
    Ui::DiffMatchPatch *ui;
};

#endif // DIFFMATCHPATCH_H

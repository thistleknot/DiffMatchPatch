#include "diffmatchpatch.h"
#include "ui_diffmatchpatch.h"

#include <QApplication>
#include <QPushButton>
#include <QVBoxLayout>

#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>


DiffMatchPatch::DiffMatchPatch(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DiffMatchPatch)
{
    ui->setupUi(this);
}

PatchOutputWindow *childForm;

DiffMatchPatch::~DiffMatchPatch()
{
    delete ui;
}

QString returnQstring(QString *parent = 0)
{
    return *parent;
}

void DiffMatchPatch::on_actionOpen_Left_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), QString(),
                                                    tr("Text Files (*.txt);;C++ Files (*.cpp *.h)"));

    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
            return;
        }
        QTextStream in(&file);
        //ui->plainTextEditLeft->setText(in.readAll());

        //set font to ASCII
        //http://qt-project.org/forums/viewthread/7943
        //ui->plainTextEditLeft->setStyleSheet("font: 9pt \"Courier\";");

        //no wrap
        //http://qt-project.org/doc/qt-4.8/qtextedit.html#LineWrapMode-enum
        //http://qt-project.org/doc/qt-4.8/qtextedit.html#lineWrapMode-prop
        //how to use
        //http://www.qtcentre.org/threads/8188-bug-setLineWrapMode
        //setLineWrapMode(QTextEdit::NoWrap)

        //plainTextEditLeft.setLineWrapMode(plainTextEdit::NoWrap);
        ui->plainTextEditLeft->setLineWrapMode(QPlainTextEdit::NoWrap);

        ui->plainTextEditLeft->setPlainText(in.readAll());
        //ui->textEditLeft->setText(in.readAll());
        file.close();
    }
}

void DiffMatchPatch::on_actionOpen_Right_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), QString(),
                                                    tr("Text Files (*.txt);;C++ Files (*.cpp *.h)"));

    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
            return;
        }
        QTextStream in(&file);

        ui->plainTextEditRight->setStyleSheet("font: 9pt \"Courier\";");

        ui->plainTextEditRight->setLineWrapMode(QPlainTextEdit::NoWrap);

        ui->plainTextEditRight->setPlainText(in.readAll());

        file.close();
    }
}

void DiffMatchPatch::on_actionSave_Left_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), QString(),
                                                    tr("Text Files (*.txt);;C++ Files (*.cpp *.h)"));

    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly)) {
            // error message
        } else {
            QTextStream stream(&file);
            stream << ui->plainTextEditLeft->toPlainText();
            stream.flush();
            file.close();
        }
    }
}

void DiffMatchPatch::on_actionSave_Right_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), QString(),
                                                    tr("Text Files (*.txt);;C++ Files (*.cpp *.h)"));

    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly)) {
            // error message
        } else {
            QTextStream stream(&file);
            stream << ui->plainTextEditRight->toPlainText();
            stream.flush();
            file.close();
        }
    }
}



void DiffMatchPatch::on_actionPatch_Compute_triggered()
{
    diff_match_patch dmp;

    QString str1 = ui->plainTextEditLeft->toPlainText();
    QString str2 = ui->plainTextEditRight->toPlainText();

    childForm = new PatchOutputWindow(this);

    //parent window can be in front of child window
    //childForm = new PatchOutputWindow();

    QString strPatch = dmp.patch_toText(dmp.patch_make(str1, str2));
    QTextStream out(&strPatch);

    childForm->setOutputWindowText(strPatch);

    childForm->show();

    //emit patchOutputWindowData(&strPatch);

    //manually create a new window
    /*
    QWidget* win = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout(win);
    QPlainTextEdit* plainTextEditPatchOutput = new QPlainTextEdit();

    layout->addWidget(plainTextEditPatchOutput);

    //Load up patch file into a string
    QString strPatch = dmp.patch_toText(dmp.patch_make(str1, str2));
    QTextStream out(&strPatch);

    plainTextEditPatchOutput->setStyleSheet("font: 9pt \"Courier\";");
    plainTextEditPatchOutput->setLineWrapMode(QPlainTextEdit::NoWrap);

    //load patch file into plainTextEdit.
    plainTextEditPatchOutput->setPlainText(out.readAll());;

    //show window with patch file loaded
    win->show();
    */

}

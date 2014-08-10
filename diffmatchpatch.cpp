#include "diffmatchpatch.h"
#include "ui_diffmatchpatch.h"

#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>

#include <diff_match_patch.h>

DiffMatchPatch::DiffMatchPatch(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DiffMatchPatch)
{
    ui->setupUi(this);
}

DiffMatchPatch::~DiffMatchPatch()
{
    delete ui;
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
        ui->plainTextEditLeft->setStyleSheet("font: 9pt \"Courier\";");

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

void DiffMatchPatch::on_actionCompute_Patch_triggered()
{
    diff_match_patch dmp;
    QString str1 = QString("First string in diff");
    QString str2 = QString("Second string in diff");

    QString strPatch = dmp.patch_toText(dmp.patch_make(str1, str2));
    QPair<QString, QVector<bool> > out
        = dmp.patch_apply(dmp.patch_fromText(strPatch), str1);
    QString strResult = out.first;
}

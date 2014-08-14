#include "patchoutputwindow.h"
#include "ui_patchoutputwindow.h"

#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>

PatchOutputWindow::PatchOutputWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PatchOutputWindow)
{
    ui->setupUi(this);

}

void PatchOutputWindow::setOutputWindowText(QString outputString) {

    ui->plainTextEditPatchOutput->setStyleSheet("font: 9pt \"Courier\";");

    ui->plainTextEditPatchOutput->setLineWrapMode(QPlainTextEdit::NoWrap);

    ui->plainTextEditPatchOutput->setPlainText(outputString);
}

PatchOutputWindow::~PatchOutputWindow()
{
    delete ui;
}


void PatchOutputWindow::on_actionSave_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), QString(),
            tr("Text Files (*.txt);;C++ Files (*.cpp *.h)"));

    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly)) {
            // error message
        } else {
            QTextStream stream(&file);
            stream << ui->plainTextEditPatchOutput->toPlainText();
            stream.flush();
            file.close();
        }
    }

}


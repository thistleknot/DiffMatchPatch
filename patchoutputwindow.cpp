#include "patchoutputwindow.h"
#include "ui_patchoutputwindow.h"

PatchOutputWindow::PatchOutputWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PatchOutputWindow)
{
    ui->setupUi(this);
}

PatchOutputWindow::~PatchOutputWindow()
{
    delete ui;
}

#include "diffmatchpatch.h"
#include <QApplication>
#include <QPushButton>
#include <QVBoxLayout>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DiffMatchPatch w;
    w.show();

    //button layout example
    /*
    QApplication app(argc, argv);
    QWidget* win = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout(win);
    QPushButton* but1 = new QPushButton("Horizontal");
    but1->resize(70,20);
    layout->addWidget(but1);
    QPushButton* but2 = new QPushButton("Vertical");
    but2->resize(70,20);
    layout->addWidget(but2);

    win->show();
    */

    return a.exec();
}

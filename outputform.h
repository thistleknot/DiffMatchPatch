#ifndef OUTPUTFORM_H
#define OUTPUTFORM_H

#include <QWidget>

namespace Ui {
class OutputForm;
}

class OutputForm : public QWidget
{
    Q_OBJECT

public:
    explicit OutputForm(QWidget *parent = 0);
    ~OutputForm();

private:
    Ui::OutputForm *ui;
};

#endif // OUTPUTFORM_H

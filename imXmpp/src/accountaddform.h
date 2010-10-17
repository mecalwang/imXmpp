#ifndef ACCOUNTADDFORM_H
#define ACCOUNTADDFORM_H

#include <QMainWindow>

namespace Ui {
    class accountAddForm;
}

class accountAddForm : public QMainWindow
{
    Q_OBJECT

public:
    explicit accountAddForm(QWidget *parent = 0);
    ~accountAddForm();

private:
    Ui::accountAddForm *ui;
};

#endif // ACCOUNTADDFORM_H

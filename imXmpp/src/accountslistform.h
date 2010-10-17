#ifndef ACCOUNTSLISTFORM_H
#define ACCOUNTSLISTFORM_H

#include <QMainWindow>
#include <QSettings>
#include "accountaddform.h"

namespace Ui {
    class accountsListForm;
}

class accountsListForm : public QMainWindow
{
    Q_OBJECT

public:
    explicit accountsListForm(QWidget *parent = 0);
    ~accountsListForm();

private:
    QSettings *accounts;
    accountAddForm *acForm;
    Ui::accountsListForm *ui;

private slots:
    void on_pushButton_released();
};

#endif // ACCOUNTSLISTFORM_H

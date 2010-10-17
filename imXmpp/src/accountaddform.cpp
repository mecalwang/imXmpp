#include "accountaddform.h"
#include "ui_accountaddform.h"

accountAddForm::accountAddForm(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::accountAddForm)
{
    ui->setupUi(this);
}

accountAddForm::~accountAddForm()
{
    delete ui;
}

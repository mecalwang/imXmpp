#include "accountslistform.h"
#include "ui_accountslistform.h"

accountsListForm::accountsListForm(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::accountsListForm)
{
    ui->setupUi(this);
    accounts = new QSettings("./accounts.ini",QSettings::IniFormat);
    int count=accounts->value("count").toInt();
    ui->tableWidget->setRowCount(count);
    QString ind;
    for (int i=0;i<count;i++){
        ind=ind.setNum(i);
        QString login=accounts->value(ind+"/login").toString();
        QString host=accounts->value(ind+"/host").toString();
        QString domain=accounts->value(ind+"/domain").toString();
        QTableWidgetItem *newItem = new QTableWidgetItem(login+"@"+host);
        ui->tableWidget->setItem(i, 0, newItem);
    }
}

accountsListForm::~accountsListForm()
{
    delete ui;
}

void accountsListForm::on_pushButton_released()
{
    this->acForm= new accountAddForm(this);
    acForm->setAttribute(Qt::WA_DeleteOnClose);
    acForm->show();
}

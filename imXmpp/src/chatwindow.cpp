#include "chatwindow.h"
#include "ui_chatwindow.h"

chatWindow::chatWindow(QString name,QString jid,QWidget *parent) :
    QMainWindow(parent)
{
    this->name=name;
    this->jid=jid;
    this->setWindowTitle(name);
    this->setGeometry(0,0,250,350);
    lblName=new QLabel(this);
    lblName->setText(name);
    lblName->setGeometry(5,5,this->width(),30);
    lblName->show();
    txtChat = new QTextEdit(this);
    txtChat->setGeometry(QRect(5,45,this->width()-10,200));
    txtChat->setReadOnly(true);
    txtChat->show();
    txtMessage = new textMessageEdit(this);
    connect(txtMessage,SIGNAL(returnPressed()),this,SLOT(btnSendClicked()));
    txtMessage->setGeometry(QRect(5,250,this->width()-10,100));
    txtMessage->show();
    btnSend = new QPushButton(this);
    btnSend->setGeometry(QRect(5,350,this->width()-10,50));
    btnSend->hide();
    connect(btnSend,SIGNAL(released()),this,SLOT(btnSendClicked()));
    //connect(txtMessage,SIGNAL())
}

void chatWindow::btnSendClicked(){
    if (txtMessage->toPlainText()!=""){
        QTime time=QTime::currentTime();
        emit sendMessage(this->jid,txtMessage->toPlainText());
        txtChat->append("<font color=\"blue\"><b>("+time.toString("HH:mm:ss")+")ME: </b></font>"+txtMessage->toPlainText());
        txtMessage->setText("");
    }
}
void chatWindow::messageReceived(const QXmppMessage & message){
    QTime time=QTime::currentTime();
    txtChat->append("<font color=\"red\"><b>("+time.toString("HH:mm:ss")+")"+this->name+": </b></font>"+message.body());
}
bool chatWindow::event(QEvent *e)
{
        return QWidget::event(e);
}
void chatWindow::resizeEvent(QResizeEvent *event){
    txtChat->setGeometry(5,45,this->width()-10,this->height()-txtMessage->height()-60);
    txtMessage->setGeometry(5,txtChat->height()+5+45,this->width()-10,txtMessage->height());
}

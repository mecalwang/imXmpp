#include "userlistitem.h"

userListItem::userListItem(QWidget *parent) :
    QWidget(parent)
{
    lblName = new QLabel(this);
    lblStatusText = new QLabel(this);
    lblPhoto = new QLabel(this);
    lblPhoto->setScaledContents(true);
}
void userListItem::setName(QString name){
    this->name=name;
    lblName->setText(name);
    lblName->setStyleSheet("color: grey");
    lblName->show();

}
void userListItem::setJid(QString jid){
    this->jid=jid;
}
void userListItem::setStatus(int status){
    this->status=status;
    if (status==1){
        qDebug()<<status;
        lblName->setStyleSheet("color: black");
        lblName->adjustSize();
    }
    if (status==2){
        qDebug()<<status;
        lblName->setStyleSheet("color: grey");
        lblName->adjustSize();
    }
}
void userListItem::setPhoto(QImage image){
    this->photo=image;
    this->lblPhoto->setPixmap(QPixmap::fromImage(this->photo));
}
void userListItem::setStatusText(QString statusText){
    this->statusText=statusText;
    this->lblStatusText->setText(statusText);
}
void userListItem::setClientId(QString id){
    this->clientId=id;
}

bool userListItem::event(QEvent *e)
{
    if (e->type()==3){
        emit released(this->jid);
    } else if (e->type()==10){
        emit mouseIn();
    } else if (e->type()==4){
        emit doubleClicked(this->clientId,this->name,this->jid);
    } else if(e->type()==11) {
        emit mouseOut();
    } else if (e->type()==2){
        emit pressed();
    } else {
    //qDebug()<<e->type();
        ////qDebug()<<sender();
        return QWidget::event(e);
    }
}
QString userListItem::getJid(){
    return this->jid;
}
QString userListItem::getName(){
    return this->name;
}
int userListItem::getStatus(){
    return this->status;
}
QImage userListItem::getPhoto(){
    return this->photo;
}
QString userListItem::getStatusText(){
    return this->statusText;
}
QString userListItem::getClientId(){
    return this->clientId;
}

void userListItem::resizeEvent(QResizeEvent *event){
    this->lblPhoto->setGeometry(5,5,40,40);
    this->lblName->setGeometry(50,5,this->width()-50,20);
    this->lblStatusText->setGeometry(50,25,this->width()-50,20);
}

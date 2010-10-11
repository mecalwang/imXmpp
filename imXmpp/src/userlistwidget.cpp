#include "userlistwidget.h"

userListWidget::userListWidget(QWidget *parent) :
    QWidget(parent)
{
    scrollArea = new QScrollArea(this);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setGeometry(0,0,this->width(),this->height());
    mainFrame = new QFrame;
    //scrollArea->setWidgetResizable(true);
    mainFrame->show();
    scrollArea->setWidget(mainFrame);
    this->showOffline=false;
}
void userListWidget::append(userListItem *item){

}
void userListWidget::append(QString clientId,QString bareJid,QString name){
    userListItem *item=new userListItem(this->mainFrame);
    item->setJid(bareJid);
    item->setName(name);
    item->setStatus(0);
    item->setClientId(clientId);
    item->setObjectName(bareJid);
    //item->show();
    connect(item,SIGNAL(doubleClicked(QString,QString,QString)),this,SLOT(itemDoubleClicked(QString,QString,QString)));
    userListItems.append(item);
    this->redrawList();
}
void userListWidget::resizeEvent(QResizeEvent * event){
    this->scrollArea->setGeometry(0,0,this->width(),this->height());
}
int userListWidget::findByJid(QString jid){
    int count=userListItems.count();
    for (int i=0;i<count;i++){
        if (userListItems[i]->getJid()==jid){
            return i;
        }
    }
    return -1;
}
void userListWidget::setStatus(QString jid,int status){
    int count=userListItems.count();
    for (int i=0;i<count;i++){
        if (userListItems[i]->getJid()==jid){
            qDebug()<<"Setting status for: "<<userListItems[i]->getJid();
            userListItems[i]->setStatus(status);
        }
    }
    this->redrawList();
}
void userListWidget::setStatusText(QString jid,QString statusText){
    int count=userListItems.count();
    for (int i=0;i<count;i++){
        if (userListItems[i]->getJid()==jid){
            qDebug()<<"Setting status text for: "<<userListItems[i]->getJid();
            userListItems[i]->setStatusText(statusText);
        }
    }
    this->redrawList();
}
void userListWidget::setPhoto(QString jid,QImage photo){
    int count=userListItems.count();
    for (int i=0;i<count;i++){
        if (userListItems[i]->getJid()==jid){
            qDebug()<<"Setting photo for: "<<userListItems[i]->getJid();
            userListItems[i]->setPhoto(photo);
        }
    }
    this->redrawList();
}
void userListWidget::itemDoubleClicked(QString clientId,QString name,QString jid){

    emit openChatWindow(clientId,name,jid);
}
void userListWidget::setShowOffline(bool show){
    this->showOffline=show;
    this->redrawList();
}
void userListWidget::redrawList(){
    int count=userListItems.count();
    int q=0;
    for (int i=0;i<count;i++){
        if (userListItems[i]->getStatus()==1){
            qDebug()<<"Online: "<<userListItems[i]->getJid();
            userListItems[i]->setGeometry(0,q*50,this->width(),50);
            userListItems[i]->show();
            mainFrame->setGeometry(0,0,scrollArea->width(),(q+1)*50);
            q++;
        } else {
            userListItems[i]->hide();
        }
    }

}

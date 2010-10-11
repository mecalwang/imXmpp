#include "imxmpp.h"

imXmpp::imXmpp(QObject *parent) :
    QObject(parent)
{
    userListForm = new userList;
    connect(userListForm,SIGNAL(sigOpenChatWindow(QString,QString,QString)),this,SLOT(openChatWindow(QString,QString,QString)));
    userListForm->show();
    //chatForm = new chatWindow;
    acManager = new accountsManager;
    connection *con;
    con = new connection(this);
    connect(con,SIGNAL(presenceReceived(QString,QString,QString,int,QString)),userListForm,SLOT(presenceReceived(QString,QString,QString,int,QString)));
    connect(con,SIGNAL(rosterResieved(QString,QHash<QString,QString>)),userListForm,SLOT(rosterResieved(QString,QHash<QString,QString>)));
    connect(con,SIGNAL(vCardReseived(QString,QString,QImage)),userListForm,SLOT(vCardReseived(QString,QString,QImage)));
    connect(con,SIGNAL(messageReceived(QString,QString,QString,QString)),this,SLOT(messageReceived(QString,QString,QString,QString)));
    con->connectToServer(1);
    con = new connection(this);
    connect(con,SIGNAL(presenceReceived(QString,QString,QString,int,QString)),userListForm,SLOT(presenceReceived(QString,QString,QString,int,QString)));
    connect(con,SIGNAL(rosterResieved(QString,QHash<QString,QString>)),userListForm,SLOT(rosterResieved(QString,QHash<QString,QString>)));
    connect(con,SIGNAL(vCardReseived(QString,QString,QImage)),userListForm,SLOT(vCardReseived(QString,QString,QImage)));
    connect(con,SIGNAL(messageReceived(QString,QString,QString,QString)),this,SLOT(messageReceived(QString,QString,QString,QString)));
    con->connectToServer(0);
}
void imXmpp::messageReceived(QString clientId, QString fromJid, QString fromBareJid, QString body){
    if (body!=""){
        qDebug()<<"Message reseived from: "<<fromBareJid;
        bool founded;
        for (int i=0;i<this->chatWindows.count();i++){
            if (this->chatWindows[i]->objectName()==fromBareJid){
                qDebug("Window founded!");
                founded=true;
                chatWindows[i]->messageReceived(clientId, fromJid, fromBareJid, body);
                break;
            }
        }
        if (!founded){
            qDebug("Creating new window!");
            connection *c = this->findChild<connection *>(clientId);
            QString name = c->getNameByBareJid(fromBareJid);
            if (name==""){
                name=fromBareJid;
            }
            chatWindow *chtW = new chatWindow(clientId,name,fromBareJid);
            chtW->setAttribute(Qt::WA_DeleteOnClose);
            chtW->setObjectName(fromBareJid);
            connect(chtW,SIGNAL(sendMessage(QString,QString,QString)),this,SLOT(sendMessage(QString,QString,QString)));
            connect(chtW,SIGNAL(chatWindowClosed(QString)),this,SLOT(chatWindowClosed(QString)));
            chtW->show();
            chatWindows.append(chtW);
            chtW->messageReceived(clientId, fromJid, fromBareJid, body);
        }
    }
}
void imXmpp::sendMessage(QString clientId,QString bareJid,QString body){
    connection *c = this->findChild<connection *>(clientId);
    c->sendMessage(bareJid,body);
}
void imXmpp::chatWindowClosed(QString jid){
    for (int i=0;i<this->chatWindows.count();i++){
        if (this->chatWindows[i]->objectName()==jid){
            this->chatWindows.remove(i);
            break;
        }
    }
}
void imXmpp::openChatWindow(QString clientId,QString name,QString jid){
    bool founded;
    for (int i=0;i<this->chatWindows.count();i++){
        if (this->chatWindows[i]->objectName()==jid){
            qDebug("Window founded!");
            founded=true;
            break;
        }
    }
    if (!founded){
        qDebug("Creating new window!");
        if (name==""){
            name=jid;
        }
        chatWindow *chtW = new chatWindow(clientId,name,jid);
        chtW->setAttribute(Qt::WA_DeleteOnClose);
        chtW->setObjectName(jid);
        connect(chtW,SIGNAL(sendMessage(QString,QString,QString)),this,SLOT(sendMessage(QString,QString,QString)));
        connect(chtW,SIGNAL(chatWindowClosed(QString)),this,SLOT(chatWindowClosed(QString)));
        chtW->show();
        chatWindows.append(chtW);
    }
}

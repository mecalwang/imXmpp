#include "connection.h"

connection::connection(QObject *parent) :
    QObject(parent)
{

}
void connection::connectToServer(int accountId){
    QSettings *settings = new QSettings("./accounts.ini",QSettings::IniFormat);
    QString id;
    id.setNum(accountId);
    QString protocol = settings->value(id+"/protocol").toString();
    QString login;
    QString pass;
    QString host;
    QString domain;
    qDebug()<<"Protocol is: "<<protocol;
    if (protocol=="gtalk"){
        login=settings->value(accountId+"/login").toString();;
        pass=settings->value(accountId+"/pass").toString();;
        host="talk.google.com";
        domain="gmail.com";
        xmppClient = new QXmppClient(this);
        //QXmppLogger::getLogger()->setLoggingType(QXmppLogger::STDOUT);
        QXmppRosterManager *rosterManager = &xmppClient->rosterManager();
        QXmppVCardManager *vCardManager = &xmppClient->vCardManager();
        connect(xmppClient,SIGNAL(connected()),this,SLOT(connected()));
        connect(xmppClient,SIGNAL(error(QXmppClient::Error)),this,SLOT(error(QXmppClient::Error)));
        connect(xmppClient,SIGNAL(disconnected()),this,SLOT(connected()));
        connect(xmppClient,SIGNAL(presenceReceived(QXmppPresence)),this,SLOT(presenceReceived(QXmppPresence)));
        connect(xmppClient,SIGNAL(messageReceived(QXmppMessage)),this,SLOT(messageReceived(QXmppMessage)));
        connect(rosterManager,SIGNAL(rosterReceived()),this,SLOT(rosterResieved()));
        connect(vCardManager,SIGNAL(clientVCardReceived()),this,SLOT(clientVCardReceived()));
        connect(vCardManager,SIGNAL(vCardReceived(QXmppVCard)),this,SLOT(vCardReceived(QXmppVCard)));
        connect(xmppClient,SIGNAL(discoveryIqReceived(QXmppDiscoveryIq)),this,SLOT(connected()));
        connect(xmppClient,SIGNAL(iqReceived(QXmppIq)),this,SLOT(connected()));
        //xmppClient->connectToServer(host,login,pass,domain);
        xmppClient->connectToServer("talk.google.com","lezhoev","07493957","gmail.com");
    } else if (protocol=="vk") {
        login=settings->value(accountId+"/login").toString();
        pass=settings->value(accountId+"/pass").toString();
        host="vkmessenger.com";
        domain="vk.com";
        xmppClient = new QXmppClient(this);
        //QXmppLogger::getLogger()->setLoggingType(QXmppLogger::STDOUT);
        QXmppRosterManager *rosterManager = &xmppClient->rosterManager();
        QXmppVCardManager *vCardManager = &xmppClient->vCardManager();
        connect(xmppClient,SIGNAL(connected()),this,SLOT(connected()));
        connect(xmppClient,SIGNAL(error(QXmppClient::Error)),this,SLOT(error(QXmppClient::Error)));
        connect(xmppClient,SIGNAL(disconnected()),this,SLOT(connected()));
        connect(xmppClient,SIGNAL(presenceReceived(QXmppPresence)),this,SLOT(presenceReceived(QXmppPresence)));
        connect(xmppClient,SIGNAL(messageReceived(QXmppMessage)),this,SLOT(messageReceived(QXmppMessage)));
        connect(rosterManager,SIGNAL(rosterReceived()),this,SLOT(rosterResieved()));
        connect(vCardManager,SIGNAL(clientVCardReceived()),this,SLOT(clientVCardReceived()));
        connect(vCardManager,SIGNAL(vCardReceived(QXmppVCard)),this,SLOT(vCardReceived(QXmppVCard)));
        connect(xmppClient,SIGNAL(discoveryIqReceived(QXmppDiscoveryIq)),this,SLOT(connected()));
        connect(xmppClient,SIGNAL(iqReceived(QXmppIq)),this,SLOT(connected()));
        //xmppClient->connectToServer(host,login,pass,domain);
        xmppClient->connectToServer("vkmessenger.com","id2615106","1dac052","vk.com");
    } else if (protocol=="icq") {

    } else {
        login=settings->value(accountId+"/login").toString();
        pass=settings->value(accountId+"/pass").toString();
        host=settings->value(accountId+"/host").toString();
        domain=settings->value(accountId+"/domain").toString();
        xmppClient = new QXmppClient(this);
        //QXmppLogger::getLogger()->setLoggingType(QXmppLogger::STDOUT);
        QXmppRosterManager *rosterManager = &xmppClient->rosterManager();
        QXmppVCardManager *vCardManager = &xmppClient->vCardManager();
        connect(xmppClient,SIGNAL(connected()),this,SLOT(connected()));
        connect(xmppClient,SIGNAL(error(QXmppClient::Error)),this,SLOT(error(QXmppClient::Error)));
        connect(xmppClient,SIGNAL(disconnected()),this,SLOT(connected()));
        connect(xmppClient,SIGNAL(presenceReceived(QXmppPresence)),this,SLOT(presenceReceived(QXmppPresence)));
        connect(xmppClient,SIGNAL(messageReceived(QXmppMessage)),this,SLOT(messageReceived(QXmppMessage)));
        connect(rosterManager,SIGNAL(rosterReceived()),this,SLOT(rosterResieved()));
        connect(vCardManager,SIGNAL(clientVCardReceived()),this,SLOT(clientVCardReceived()));
        connect(vCardManager,SIGNAL(vCardReceived(QXmppVCard)),this,SLOT(vCardReceived(QXmppVCard)));
        connect(xmppClient,SIGNAL(discoveryIqReceived(QXmppDiscoveryIq)),this,SLOT(connected()));
        connect(xmppClient,SIGNAL(iqReceived(QXmppIq)),this,SLOT(connected()));
        xmppClient->connectToServer(host,login,pass,domain);
    }
}
void connection::disconnect(){

}

void connection::error(QXmppClient::Error){
    qDebug("ERROR!!!!!!!!!!!!");
}
void connection::connected(){

    this->clientId=xmppClient->getConfiguration().getJid();
    emit connected(clientId);
    qDebug()<<clientId<<" connected!";
    /*this->logged=true;
    list->show();*/

}
void connection::disconnected(){
    qDebug()<<this->clientId<<" disconnected!";
}
void connection::error(){
    qDebug("ERROR!!!!!!!");
}
void connection::rosterResieved(){
    qDebug()<<this->clientId<<" rosterResieved!";
/*
   // rosterManager= client->rosterManager();
    QStringList bareJids = client->rosterManager().getRosterBareJids();
    QString name;
    for (int i=0;i<bareJids.size();i++){
        qDebug()<<bareJids.at(i);
        QXmppRosterIq::Item rosterIq = client->rosterManager().getRosterEntry(bareJids.at(i));
        if (rosterIq.getName()==""){
            name=rosterIq.getBareJid();
        } else {
            name=rosterIq.getName();
        }
        list->append(rosterIq.getBareJid(),name);

    }*/
}
void connection::presenceReceived(const QXmppPresence & presence){
    qDebug()<<this->clientId<<" presenceResieved!";
    int status = presence.getType();
    QString statusText = presence.getStatus().getStatusText();
    QString fromBareJid = presence.getFrom().left(presence.getFrom().indexOf("/"));
    QString fromJid = presence.getFrom();
    /*//qDebug()<<presence.type();
    qDebug()<<presence.getType();
    QString jid=presence.getFrom().left(presence.getFrom().indexOf("/"));
    //client->vCardManager().requestVCard(jid);
    this->list->setStatus(jid,presence.getType());
    this->list->setStatusText(jid,presence.getStatus().getStatusText());*/
    emit presenceReceived(this->clientId,fromJid,fromBareJid,status,statusText);
}
void connection::messageReceived(const QXmppMessage & message){
    qDebug()<<this->clientId<<" messageReceived!";
        QString fromJid=message.getFrom();
        QString fromBareJid=message.getFrom();
        QString body=message.getBody();
        emit this->messageReceived(this->clientId,fromJid,fromBareJid,body);

}
void connection::vCardReceived(QXmppVCard vCard){
    qDebug()<<this->clientId<<" vCardReceived!";
    /*QString jid = vCard.getFrom();
    QImage photo = vCard.getPhotoAsImage();
    list->setPhoto(jid,photo);*/
}
void connection::clientVCardReceived(){
    qDebug("clientVCardReceived!!!");
}
/*void connection::sendMessage(QString to,QString msg){
    //this->client->sendPacket(QXmppMessage(client->getConfiguration().getJid(),to , msg));
    //qDebug()<<client->getConfiguration().getJid();
    //this->client->sendMessage(to,msg);
    qDebug("Message sended!!!");
}*/

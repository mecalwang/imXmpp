#include "connection.h"

connection::connection(QObject *parent) :
    QObject(parent)
{

}
void connection::connectToServer(int accountId){
    QSettings *settings = new QSettings("./accounts.ini",QSettings::IniFormat);
    crypting cry;
    QString id;
    id.setNum(accountId);
    QString protocol = settings->value(id+"/protocol").toString();
    QString login;
    QString pass;
    QString host;
    QString domain;
    qDebug()<<"Protocol is: "<<protocol;
    if (protocol=="gtalk"){
        login=settings->value(id+"/login").toString();;
        pass=cry.decrypt(settings->value(id+"/pass").toString());
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
        xmppClient->connectToServer(host,login,pass,domain);
    } else if (protocol=="vk") {
        login=settings->value(id+"/login").toString();
        pass=cry.decrypt(settings->value(id+"/pass").toString());
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
        xmppClient->connectToServer(host,login,pass,domain);
    } else if (protocol=="icq") {

    } else {
        login=settings->value(id+"/login").toString();
        pass=settings->value(id+"/pass").toString();
        host=settings->value(id+"/host").toString();
        domain=settings->value(id+"/domain").toString();
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
    this->setObjectName(clientId);
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
    QHash<QString,QString> roster;

   // rosterManager= client->rosterManager();
    QStringList bareJids = xmppClient->rosterManager().getRosterBareJids();
    QString name;
    for (int i=0;i<bareJids.size();i++){
        QXmppRosterIq::Item rosterIq = xmppClient->rosterManager().getRosterEntry(bareJids.at(i));
        if (rosterIq.getName()==""){
            name=rosterIq.getBareJid();
        } else {
            name=rosterIq.getName();
        }
        roster[rosterIq.getBareJid()]=name;
    }
    emit rosterResieved(this->clientId,roster);
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
    xmppClient->vCardManager().requestVCard(fromBareJid);
}
void connection::messageReceived(const QXmppMessage & message){
    qDebug()<<this->clientId<<" messageReceived!";
        QString fromJid=message.getFrom();
        QString fromBareJid=message.getFrom();
        fromBareJid=fromBareJid.left(fromBareJid.indexOf("/"));
        QString body=message.getBody();
        emit this->messageReceived(this->clientId,fromJid,fromBareJid,body);

}
void connection::vCardReceived(QXmppVCard vCard){
    qDebug()<<this->clientId<<" vCardReceived!";
    QImage photo = vCard.getPhotoAsImage();
    QString fromBareJid = vCard.getFrom();
    emit vCardReseived(this->clientId,fromBareJid,photo);
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
QString connection::getNameByBareJid(QString bareJid){
    return xmppClient->rosterManager().getRosterEntry(bareJid).getName();
}
void connection::sendMessage(QString bareJid, QString body){
    qDebug()<<"sendMessage to "<<bareJid;
    bareJid=bareJid.left(bareJid.indexOf("/"));
    xmppClient->sendMessage(bareJid,body);
}

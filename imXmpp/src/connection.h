#ifndef CONNECTION_H
#define CONNECTION_H

#include <QObject>
#include <QSettings>

#include "QXmppClient.h"
#include "QXmppRosterManager.h"
#include "QXmppLogger.h"
#include "QXmppPresence.h"
#include "QXmppMessage.h"
#include "QXmppRosterIq.h"
#include <QXmppConfiguration.h>
#include <QXmppVersionIq.h>
#include <QXmppVCardManager.h>

#include <QXmppDiscoveryIq.h>
#include <QXmppIq.h>

#include <QList>
#include <QHash>
class connection : public QObject
{
    Q_OBJECT
public:
    explicit connection(QObject *parent = 0);
    void connectToServer(int accountId);
    void disconnect();
private:
    QXmppClient *xmppClient;
    QString clientId;
    QHash<QString,QString> roster;
    QHash<QString,QString> presence;
    QHash<QString,QString> message;

signals:
    void connected(QString clientId);
    void disconnected(QString clientId);
    void error(QString clientId);
    void rosterResieved(QString clientId);
    void presenceReceived(QString clientId,QString fromJid,QString fromBareJid,int status,QString statusText);
    void messageReceived(QString clientId,QString fromJid,QString fromBareJid,QString body);
public slots:
    void connected();
    void disconnected();
    void error();
    void rosterResieved();
    void presenceReceived(const QXmppPresence &);
    void messageReceived(const QXmppMessage &);


    void error(QXmppClient::Error);
    void clientVCardReceived();
    void vCardReceived(QXmppVCard);
};

#endif // CONNECTION_H

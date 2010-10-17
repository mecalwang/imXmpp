#ifndef IMXMPP_H
#define IMXMPP_H

#include <QObject>
#include "userlist.h"
#include "chatwindow.h"
#include "accountsmanager.h"
#include "connection.h"
#include "accountslistform.h"

class imXmpp : public QObject
{
    Q_OBJECT
public:
    explicit imXmpp(QObject *parent = 0);
private:
    userList *userListForm;
    chatWindow *chatForm;
    accountsManager *acManager;
    QVector<chatWindow *> chatWindows;

signals:

public slots:

private slots:
    void messageReceived(QString clientId,QString fromJid,QString fromBareJid,QString body);
    void sendMessage(QString clientId,QString bareJid,QString body);
    void chatWindowClosed(QString jid);
    void openChatWindow(QString clientId,QString name,QString jid);
    void openAccountsListForm();
};

#endif // IMXMPP_H

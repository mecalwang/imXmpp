#ifndef IMXMPP_H
#define IMXMPP_H

#include <QObject>
#include "userlist.h"
#include "chatwindow.h"
#include "accountsmanager.h"
#include "connection.h"

class imXmpp : public QObject
{
    Q_OBJECT
public:
    explicit imXmpp(QObject *parent = 0);
private:
    userList *userListForm;
    chatWindow *chatForm;
    accountsManager *acManager;

signals:

public slots:

};

#endif // IMXMPP_H

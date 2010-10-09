#ifndef IMXMPP_H
#define IMXMPP_H

#include <QObject>
#include "userlist.h"
#include "chatwindow.h"
#include "accounsmanager.h"

class imXmpp : public QObject
{
    Q_OBJECT
public:
    explicit imXmpp(QObject *parent = 0);

signals:

public slots:

};

#endif // IMXMPP_H

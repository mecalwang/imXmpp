#include "imxmpp.h"

imXmpp::imXmpp(QObject *parent) :
    QObject(parent)
{
    userListForm = new userList;
    userListForm->show();
    //chatForm = new chatWindow;
    acManager = new accountsManager;
    connection *con;
    con = new connection;
    connect(con,SIGNAL(presenceReceived(QString,QString,QString,int,QString)),userListForm,SLOT(presenceReceived(QString,QString,QString,int,QString)));
    con->connectToServer(1);
    con = new connection;
    connect(con,SIGNAL(presenceReceived(QString,QString,QString,int,QString)),userListForm,SLOT(presenceReceived(QString,QString,QString,int,QString)));
    con->connectToServer(0);
}

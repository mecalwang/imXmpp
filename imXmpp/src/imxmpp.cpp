#include "imxmpp.h"

imXmpp::imXmpp(QObject *parent) :
    QObject(parent)
{
    userListForm = new userList;
    //chatForm = new chatWindow;
    acManager = new accountsManager;
    connection *con;
    con = new connection;
    con->connectToServer(1);
    con = new connection;
    con->connectToServer(0);
}

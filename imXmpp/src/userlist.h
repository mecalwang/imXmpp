#ifndef USERLIST_H
#define USERLIST_H

#include <QWidget>
#include <QDesktopWidget>
#include <QDebug>
#include <QLineEdit>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QHash>
#include <QMouseEvent>
#include "chatwindow.h"
#include "QListWidgetItem"
#include "userlistitem.h"
#include "userlistwidget.h"

#include <QApplication>

#include <QSettings>

class userList : public QWidget {
    Q_OBJECT
public:
    userList(QWidget *parent = 0);

protected:
    void changeEvent(QEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void focusInEvent(QFocusEvent *event);
    void focusOutEvent(QFocusEvent *event);
    //void moveEvent(QMoveEvent *event);
    void stickyMoveEvent(QMouseEvent *event);

private:
    bool event(QEvent *e);

    QString snapped;
    QPoint dragPos;

    bool isClosed;



    QAction *minimizeAction;
    QAction *maximizeAction;
    QAction *restoreAction;
    QAction *quitAction;
    QAction *settingsFormAction;
    QAction *aboutAction;

    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;
    void createActions();
    void createTrayIcon();


    QLabel *lblLogin;
    QLabel *lblPass;
    QLineEdit *txtLogin;
    QLineEdit *txtPass;
    QPushButton *pbtLogin;

    userListWidget *list;
    void resizeEvent ( QResizeEvent * event );
    void closeEvent(QCloseEvent *);
signals:
    void sigOpenChatWindow(QString clientId,QString name,QString jid);
private slots:
    void iconActivated(QSystemTrayIcon::ActivationReason reason);
    void showForm();
    void closeForm();
    void quit();
    void openChatWindow(QString clientId,QString name,QString jid);


public slots:
    void rosterResieved(QString clientId, QHash<QString,QString> roster);
    void vCardReseived(QString clientId,QString fromBareJid,QImage photo);
    void presenceReceived(QString clientId,QString fromJid,QString fromBareJid,int status,QString statusText);
};

#endif // USERLIST_H

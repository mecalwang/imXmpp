#ifndef USERLIST_H
#define USERLIST_H

#include <QWidget>
#include <QDesktopWidget>
#include <QDebug>
#include <QLineEdit>
#include <QSystemTrayIcon>
#include <QMenu>

#include <QMouseEvent>
#include "chatwindow.h"
#include "QListWidgetItem"
#include "userlistitem.h"
#include "userlistwidget.h"
#include "xmppclient.h"


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
    bool logged;
    QString snapped;
    QPoint dragPos;

    bool isClosed;

    QSettings *accountsSettings;

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
private slots:
    void iconActivated(QSystemTrayIcon::ActivationReason reason);
    void showForm();
    void closeForm();
    void quit();
    void openChatWindow(QString,QString);


    void chatWindowClosed(chatWindow *);
    void login();

};

#endif // USERLIST_H

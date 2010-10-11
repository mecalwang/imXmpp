#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QDebug>
#include <QTime>
#include <QKeyEvent>
#include <QTextEdit>
#include <QListWidget>
#include <QPushButton>
#include <QXmppMessage.h>
#include "textmessageedit.h"

class chatWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit chatWindow(QString clientId,QString name,QString bareJid,QWidget *parent = 0);
signals:
    void sendMessage(QString clientId,QString bareJid,QString body);
    void chatWindowClosed(QString jid);
private:
    bool event(QEvent *e);
    QString name;
    QString jid;
    QString clientId;
    QLabel *lblName;
    QTextEdit *txtChat;
    textMessageEdit *txtMessage;
    QPushButton *btnSend;
    void resizeEvent(QResizeEvent *);
    void closeEvent(QCloseEvent *);
public slots:
    void messageReceived(QString clientId, QString fromJid, QString fromBareJid, QString body);
private slots:
    void btnSendClicked();
};

#endif // CHATWINDOW_H

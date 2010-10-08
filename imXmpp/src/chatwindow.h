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
    explicit chatWindow(QString,QString,QWidget *parent = 0);
signals:
    void sendMessage(QString,QString);
    void closed(chatWindow *);
private:
    bool event(QEvent *e);
    QString name;
    QString jid;
    QLabel *lblName;
    QTextEdit *txtChat;
    textMessageEdit *txtMessage;
    QPushButton *btnSend;
    void resizeEvent(QResizeEvent *);
public slots:
    void messageReceived(const QXmppMessage &);
private slots:
    void btnSendClicked();
};

#endif // CHATWINDOW_H

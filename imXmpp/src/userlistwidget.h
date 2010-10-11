#ifndef USERLISTWIDGET_H
#define USERLISTWIDGET_H

#include <QWidget>
#include <userlistitem.h>
#include <QScrollArea>

class userListWidget : public QWidget
{
    Q_OBJECT
public:
    explicit userListWidget(QWidget *parent = 0);
    void append(userListItem *);
    void append(QString clientId,QString bareJid,QString name);
    int findByJid(QString);
    void setStatus(QString jid, int status);
    void setStatusText(QString jid, QString statusText);
    void setPhoto(QString jid, QImage photo);
    void setShowOffline(bool);
private:
    QVector<userListItem*> userListItems;
    QScrollArea *scrollArea;
    QFrame *mainFrame;
    void resizeEvent ( QResizeEvent * event );
    void redrawList();
    bool showOffline;
signals:
    void openChatWindow(QString clientId,QString name,QString jid);
public slots:
    void itemDoubleClicked(QString clientId,QString name,QString jid);

};

#endif // USERLISTWIDGET_H

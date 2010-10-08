#ifndef USERLISTITEM_H
#define USERLISTITEM_H

#include <QWidget>
#include <QLabel>
#include <QImage>
#include <QPixmap>
#include <QDebug>
#include <QEvent>

class userListItem : public QWidget
{
    Q_OBJECT
public:
    explicit userListItem(QWidget *parent = 0);
    void setName(QString);
    void setJid(QString);
    void setStatus(int);
    void setStatusText(QString);
    void setPhoto(QImage);
    QString getName();
    QString getJid();
    QImage getPhoto();
    int getStatus();
    QString getStatusText();
private:
    QString name;
    QString jid;
    int status;
    QImage photo;
    QString statusText;

    QLabel *lblName;
    QLabel *lblPhoto;
    QLabel *lblStatusText;
    bool event(QEvent *e);
    void resizeEvent(QResizeEvent *);
signals:
    void released(QString);
    void doubleClicked(QString,QString);
    void mouseIn();
    void mouseOut();
    void pressed();

public slots:

};

#endif // USERLISTITEM_H

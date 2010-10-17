#ifndef CRYPT_H
#define CRYPT_H

#include <QObject>
#include <cmath>
#include <QChar>

class crypting : public QObject
{
    Q_OBJECT
public:
    explicit crypting(QObject *parent = 0);
    QString encrypt(QString input);
    QString decrypt(QString input);
private:
    QString dsCrypt(QString input,bool decrypt=false);
signals:

public slots:

};

#endif // CRYPT_H

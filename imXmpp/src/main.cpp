#include <QtGui/QApplication>
#include <QTextCodec>
#include "imxmpp.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setQuitOnLastWindowClosed(false);
    qApp->setApplicationName("imXmpp");
    qApp->setApplicationVersion("0.0.1");
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF8"));
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF8"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF8"));
    imXmpp core;
    return a.exec();
}

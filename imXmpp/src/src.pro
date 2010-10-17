#-------------------------------------------------
#
# Project created by QtCreator 2010-10-08T13:41:24
#
#-------------------------------------------------

QT += network xml
TARGET = vk-xmpp
TEMPLATE = app
SOURCES += main.cpp \
    imxmpp.cpp \
    userlist.cpp \
    chatwindow.cpp \
    userlistitem.cpp \
    userlistwidget.cpp \
    textmessageedit.cpp \
    accountsmanager.cpp \
    connection.cpp \
    accountslistform.cpp \
    crypt.cpp \
    accountaddform.cpp
HEADERS += \
    imxmpp.h \
    userlist.h \
    chatwindow.h \
    userlistitem.h \
    userlistwidget.h \
    textmessageedit.h \
    accountsmanager.h \
    connection.h \
    accountslistform.h \
    crypt.h \
    accountaddform.h
INCLUDEPATH += ../qxmpp
CONFIG(debug, debug|release) {
    LIBS += -L../qxmpp/debug -lQXmppClient_d
 } else {
    LIBS += -L../qxmpp/release -lQXmppClient
 }

RESOURCES += \
    resourses.qrc

FORMS += \
    accountslistform.ui \
    accountaddform.ui

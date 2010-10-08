#ifndef TEXTMESSAGEEDIT_H
#define TEXTMESSAGEEDIT_H

#include <QTextEdit>
#include <QKeyEvent>
#include <QEvent>
#include <QDebug>

class textMessageEdit : public QTextEdit
{
    Q_OBJECT
public:
    explicit textMessageEdit(QWidget *parent = 0);
protected:
    virtual void keyPressEvent(QKeyEvent * keyEvent);
signals:
    void returnPressed();
    void controlReturnPressed();
public slots:

};

#endif // TEXTMESSAGEEDIT_H

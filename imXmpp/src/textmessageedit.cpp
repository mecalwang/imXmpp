#include "textmessageedit.h"

textMessageEdit::textMessageEdit(QWidget *parent) :
    QTextEdit(parent)
{
}
void textMessageEdit::keyPressEvent(QKeyEvent * keyEvent)
{
        if (keyEvent->modifiers()==Qt::ControlModifier && keyEvent->key() == Qt::Key_Return){
                emit controlReturnPressed();
        } else {
            if (keyEvent->key() == Qt::Key_Return)
            {
                emit returnPressed();
            } else {
                QTextEdit::keyPressEvent(keyEvent);
            }
        }
}

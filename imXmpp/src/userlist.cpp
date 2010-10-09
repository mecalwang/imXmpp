#include "userlist.h"

userList::userList(QWidget *parent) :
    QWidget(parent)
{

    this->setGeometry(0,0,200,300);


    createActions();
    createTrayIcon();
    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));

    list=new userListWidget(this);
    list->setGeometry(5,5,this->width()-10,this->height()-10);
    connect(list,SIGNAL(openChatWindow(QString,QString)),this,SLOT(openChatWindow(QString,QString)));
    list->show();
    //client->connectToServer("vkmessenger.com","id2615106","1dac052","vk.com");
    //client->connectToServer("talk.google.com","lezhoev","07493957","gmail.com");
}

void userList::createActions()
{
    minimizeAction = new QAction(tr("Скрыть"), this);
    connect(minimizeAction, SIGNAL(triggered()), this, SLOT(closeForm()));

    //maximizeAction = new QAction(tr("Ma&ximize"), this);
    //connect(maximizeAction, SIGNAL(triggered()), this, SLOT(showMaximized()));

    restoreAction = new QAction(tr("Показать"), this);
    connect(restoreAction, SIGNAL(triggered()), this, SLOT(showForm()));

    quitAction = new QAction(tr("Выход"), this);
    connect(quitAction, SIGNAL(triggered()), this, SLOT(quit()));

    settingsFormAction = new QAction(tr("Настройки"), this);
    connect(settingsFormAction, SIGNAL(triggered()), this, SLOT(showSettingsForm()));

    aboutAction = new QAction(tr("О программе"), this);
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(showAboutForm()));
}
void userList::createTrayIcon()
{
    trayIconMenu = new QMenu(this);
    trayIconMenu->addAction(minimizeAction);
    //trayIconMenu->addAction(maximizeAction);
    trayIconMenu->addAction(restoreAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(settingsFormAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(aboutAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(quitAction);

    QIcon icon;
    icon.addFile(QString::fromUtf8(":/images/trayIcon.png"), QSize(), QIcon::Normal, QIcon::Off);

    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setIcon(icon);
    trayIcon->setVisible(1);
    trayIcon->setContextMenu(trayIconMenu);
}
void userList::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason) {
    case QSystemTrayIcon::Trigger:
    case QSystemTrayIcon::DoubleClick:
        if (isClosed){
            isClosed=false;
            showForm();
            this->clearFocus();
        } else {
            this->clearFocus();
            closeForm();

        }
        break;
    case QSystemTrayIcon::MiddleClick:
        break;
    default:
        ;
    }
}
void userList::showForm(){
    this->isClosed=false;
    QIcon icon;
    icon.addFile(QString::fromUtf8(":/images/trayIcon.png"), QSize(), QIcon::Normal, QIcon::Off);
    trayIcon->setIcon(icon);
    this->show();
}
void userList::closeForm(){
    this->isClosed=true;
    QIcon icon;
    icon.addFile(QString::fromUtf8(":/images/trayIcon2.png"), QSize(), QIcon::Normal, QIcon::Off);
    trayIcon->setIcon(icon);
    this->hide();
}
void userList::quit(){
    qApp->exit();
}





void userList::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        break;
    default:
        break;
    }
}
bool userList::event(QEvent *e)
{
    /*if (e->type()==10){
        mouseInEvent();
    } else if(e->type()==11) {
        mouseOutEvent();
    } else {*/
        return QWidget::event(e);
    //}
}
void userList::resizeEvent ( QResizeEvent * event )
{
        this->list->setGeometry(5,5,this->width()-10,this->height()-10);
}
void userList::closeEvent(QCloseEvent *event){
    this->closeForm();
    event->ignore();
}

void userList::mousePressEvent(QMouseEvent *event){
    //////qDebug()<<event->button();
    if (event->button() == 1)
    dragPos = event->pos();
    //QWidget::mousePressEvent(event);
}
void userList::mouseMoveEvent(QMouseEvent *event){
    //qDebug("mouseMoveEvent");
if( event->buttons() == Qt::LeftButton ) {
    stickyMoveEvent(event);
    event->accept();
    }
}
void userList::stickyMoveEvent(QMouseEvent *event)
{
    //qDebug("stickyMoveEvent");
//int screen_number = QApplication::desktop()->screenNumber(event->globalPos());
QRect screen_geometry = QApplication::desktop()->availableGeometry(0);

int newPosX = -1, newPosY = -1, snapFactorX = 30, snapFactorY = 30;
int event_pos_x = event->globalPos().x()- dragPos.x();
int event_pos_y = event->globalPos().y()- dragPos.y();
//////qDebug()<<  dragPos.x();

if ( qAbs(event_pos_y + height() - screen_geometry.height()) <= snapFactorY ) {
newPosY = screen_geometry.height() - height();
this->snapped="NULL";
} else if ( qAbs(event_pos_y) <= snapFactorY ) {
newPosY = 0;
this->snapped="top";
} else {
newPosY = event_pos_y;
if (snapped!="right" && snapped!="left")
this->snapped="NULL";
}

if ( qAbs(event_pos_x + width() - screen_geometry.width()) <= snapFactorX ) {
newPosX = screen_geometry.width() - width();
this->snapped="right";
} else if ( qAbs(event_pos_x) <= snapFactorX ) {
newPosX = 0;
this->snapped="left";
} else {
newPosX = event_pos_x;
this->snapped="NULL";
}

this->setGeometry(QRect(newPosX,newPosY,this->width(),this->height()));
}
void userList::mouseReleaseEvent(QMouseEvent *event){
    /*this->_x=this->x();
    this->_y=this->y();
    globalSettings->setValue("snapped",this->snapped);
    globalSettings->setValue("x",this->x());
    globalSettings->setValue("y",this->y());*/

}
void userList::focusInEvent(QFocusEvent *event){
    //qDebug("focusIn!");
}
void userList::focusOutEvent(QFocusEvent *event){
    //qDebug("focusOut!");
    //autohide();
}


void userList::openChatWindow(QString name,QString jid){
    chatWindow *chtW = new chatWindow(name,jid,this);
    chtW->setAttribute(Qt::WA_DeleteOnClose);
    chtW->setObjectName(jid);
    connect(chtW,SIGNAL(sendMessage(QString,QString)),this,SLOT(sendMessage(QString,QString)));
    connect(chtW,SIGNAL(closed(chatWindow *)),this,SLOT(chatWindowClosed(chatWindow *)));
    chtW->show();
    qDebug()<<jid;
}
void userList::chatWindowClosed(chatWindow *window){
    //delete window;
    qDebug("chatWindowDestroyed!!!");
}
void userList::presenceReceived(QString clientId,QString fromJid,QString fromBareJid,int status,QString statusText){
    list->append(fromBareJid,fromBareJid);
}

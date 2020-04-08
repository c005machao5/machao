#include <QMessageBox>
#include "roomwidget.h"
#include "ui_roomwidget.h"
#include "protocol/protocol.h"
#include "socket/socketmanager.h"
#include "scrolltext/scrolltext.h"
#include "widgetmanager.h"
#include "video/xincamera.h"

#include <QDebug>
RoomWidget::RoomWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RoomWidget)
{
    ui->setupUi(this);
    ui->lbScroll->setAttribute(Qt::WA_TranslucentBackground);
    ui->lbVideo->setAttribute(Qt::WA_TranslucentBackground);
    ui->cbCamera->setEnabled(false);
}

RoomWidget::~RoomWidget()
{
    delete ui;
}

QString RoomWidget::getRoomname() const
{
    return roomname;
}

void RoomWidget::setRoomname(const QString &value)
{
    roomname = value;
}

QString RoomWidget::getUsername() const
{
    return username;
}

void RoomWidget::setUsername(const QString &value)
{
    username = value;
}

void RoomWidget::appendText(const QString &text)
{
    ui->teShow->append(text);
}

void RoomWidget::closeEvent(QCloseEvent *event)
{
    event->ignore();

    Protocol p;
    p.setType(Protocol::room);
    p["type"] = "quit";
    p["username"] = username;
    p["roomname"] = roomname;

    SocketManager::getInstance()->write(p.pack());
}
//按回车发送消息
void RoomWidget::on_leIput_returnPressed()
{
    QString text = ui->leIput->text();
    ui->leIput->clear();

    Protocol p;
    p.setType(Protocol::chat);
    p["type"] = "chat";
    p["text"] = text;
    p["roomname"] = roomname;
    p["username"] = username;

    SocketManager::getInstance()->write(p.pack());
}

void RoomWidget::refleshUsername(QStringList userList)
{
    ui->lwUser->clear();
    ui->lwUser->addItems(userList);
}

void RoomWidget::sendScrollText(const QString &text)
{
    ScrollText::Direction d = (ScrollText::Direction) 3;//(qrand() % 4 + 1)
    //Scrolltext* st = new Scrolltext(qrand() % this->width(), qrand() % this->height(), this);
    ScrollText* st = new ScrollText(ui->lbScroll->width(),(ui->lbScroll->height()/10*(rand()%5+1)), ui->lbScroll);
    st->setText(text);
    st->setStyleSheet("color:blue");
    st->setFont(QFont("Timer",10,QFont::Black));
    st->setDirection(d);
    st->show();
    st->startScroll();

    QObject::connect(st, &ScrollText::outOfRange, [=](){
        qDebug()<<"delete";
        st->stopScroll();
        st->deleteLater();
    });
}

void RoomWidget::sendScrollGift(const QString &text)
{
    ScrollText::Direction d = (ScrollText::Direction) 3;
    ScrollText* st = new ScrollText(ui->lbVideo->width(),ui->lbVideo->height()-25, ui->lbVideo);
    st->setText(text);
    st->setStyleSheet("color:red");
    st->setFont(QFont("Timer",15,QFont::Black));
    st->setDirection(d);
    st->show();
    st->startScroll();

    QObject::connect(st, &ScrollText::outOfRange, [=](){
        qDebug()<<"delete";
        st->stopScroll();
        st->deleteLater();
    });
}

int RoomWidget::getPort() const
{
    return port;
}

void RoomWidget::setPort(int value)
{
    port = value;
}

void RoomWidget::on_pushButton_clicked() //礼物按钮
{
    WidgetManager::getInstance()->getGiftWidget()->setWindowTitle(username);
    WidgetManager::getInstance()->getGiftWidget()->setUsername(username);
    WidgetManager::getInstance()->getGiftWidget()->setRoomname(roomname);

    WidgetManager::getInstance()->getGiftWidget()->show();
}

void RoomWidget::on_checkBox_stateChanged(int arg1)
{
    if(arg1){
        ui->lbScroll->show();
    }
    else{
        ui->lbScroll->hide();
    }
}

void RoomWidget::on_btnSend_clicked()
{
    QString text = ui->leIput->text();
    ui->leIput->clear();

    Protocol p;
    p.setType(Protocol::chat);
    p["type"] = "chat";
    p["text"] = text;
    p["roomname"] = roomname;
    p["username"] = username;

    SocketManager::getInstance()->write(p.pack());
}
void RoomWidget::myInit()
{
    ui->lbVideo->clear();
    ui->lbScroll->clear();
    ui->teShow->clear();
    cmr = new XinCamera(ui->lbVideo,this->port);
    if(username==roomname){
        ui->cbCamera->setEnabled(true);
    }
}

void RoomWidget::on_cbCamera_stateChanged(int arg1)
{
    if(arg1){
        this->cmr->cameraStart();
    }else{
        this->cmr->cameraStop();
        ui->lbVideo->clear();
    }
}

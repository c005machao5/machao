#include "giftwidget.h"
#include "ui_giftwidget.h"
#include "protocol/protocol.h"
#include "socket/socketmanager.h"
#include "scrolltext/scrolltext.h"
#include "widgetmanager.h"


GiftWidget::GiftWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GiftWidget)
{
    ui->setupUi(this);
}

GiftWidget::~GiftWidget()
{
    delete ui;
}

void GiftWidget::on_btnHeart_clicked()
{
    Protocol p;
    p.setType(Protocol::gift);
    //p["type"] = "heart";
    p["money"] = 10;
    p["username"] = username;
    p["roomname"] = roomname;

    SocketManager::getInstance()->write(p.pack());
}

void GiftWidget::on_btnCar_clicked()
{
    Protocol p;
    p.setType(Protocol::gift);
    //p["type"] = "car";
    p["money"] = 50;
    p["username"] = username;
    p["roomname"] = roomname;

    SocketManager::getInstance()->write(p.pack());
}

void GiftWidget::on_btnRocket_clicked()
{
    Protocol p;
    p.setType(Protocol::gift);
    //p["type"] = "rocket";
    p["money"] = 100;
    p["username"] = username;
    p["roomname"] = roomname;

    SocketManager::getInstance()->write(p.pack());
}

void GiftWidget::on_btnDunker_clicked()
{
    Protocol p;
    p.setType(Protocol::gift);
    //p["type"] = "dunker";
    p["money"] = 200;
    p["username"] = username;
    p["roomname"] = roomname;

    SocketManager::getInstance()->write(p.pack());
}

QString GiftWidget::getUsername() const
{
    return username;
}

void GiftWidget::setUsername(const QString &value)
{
    username = value;
}

QString GiftWidget::getRoomname() const
{
    return roomname;
}

void GiftWidget::setRoomname(const QString &value)
{
    roomname = value;
}

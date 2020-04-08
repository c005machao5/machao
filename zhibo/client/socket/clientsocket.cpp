#include "clientsocket.h"
#include <QHostAddress>
#include <QMessageBox>
#include <QJsonArray>
#include <QString>

#include <QDebug>
#include "widget/widgetmanager.h"
#include "scrolltext/scrolltext.h"
ClientSocket::ClientSocket(QObject *parent)
    : QObject(parent),socket(nullptr),timer(new QTimer(this))
{
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(onTimeout()));
}

void ClientSocket::initSocket(QString ip, int port)
{
    if(this->socket != nullptr) return;

    this->ip = ip;
    this->port = port;

    //1. 创建套接字
    this->socket = new QTcpSocket(this);

    QObject::connect(this->socket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
    QObject::connect(this->socket, SIGNAL(connected()), this, SLOT(onConnected()));
    QObject::connect(this->socket, SIGNAL(disconnected()), this, SLOT(onDisConnected()));

    //2. 连接
    timer->start(1000);
}
void ClientSocket::onReadyRead()
{
    buffer += this->socket->readAll();
    Protocol p;

    while(p.unpack(buffer)){
        switch(p.getType()){
        case Protocol::chat:
            this->chatHandler(p);
            break;
        case Protocol::room:
             this->roomHandler(p);
            break;
        case Protocol::none:
            break;
        case Protocol::regist:
            this->registHandler(p);
            break;
        case Protocol::login:
            this->loginHandler(p);
            break;
        case Protocol::charge:
            this->chargeHandler(p);
            break;
        case Protocol::gift:
            this->giftHandler(p);
            break;
        }
    }
}

void ClientSocket::onTimeout()
{
    //2. 连接
    this->socket->connectToHost(QHostAddress(ip), port);
}

void ClientSocket::onConnected()
{
    qDebug()<<"连接成功";
    this->timer->stop();
}

void ClientSocket::onDisConnected()
{
    qDebug()<<"断开连接";
    this->timer->start(1000);
}
//注册
void ClientSocket::registHandler(Protocol p)
{
    QString type = p["type"].toString();
    if(type == "success"){
        //注册成功
        QMessageBox::information(WidgetManager::getInstance()->getLoginWidget(), "注册信息", p["message"].toString());
    }else if(type == "failed"){
        //注册失败
        QMessageBox::warning(WidgetManager::getInstance()->getLoginWidget(), "注册信息", p["message"].toString());
    }
}

//登录
void ClientSocket::loginHandler(Protocol p)
{
     QString type = p["type"].toString();
     if(type == "success"){
         WidgetManager::getInstance()->getHallWidget()->setWindowTitle(p["username"].toString());
         WidgetManager::getInstance()->getLoginWidget()->hide();
         WidgetManager::getInstance()->getHallWidget()->show();
     }else if(type == "failed"){
         QMessageBox::warning(WidgetManager::getInstance()->getLoginWidget(),"登录信息",p["message"].toString());
     }else if(type == "quit"){
         WidgetManager::getInstance()->getHallWidget()->hide();
         WidgetManager::getInstance()->getLoginWidget()->show();
     }
}

void ClientSocket::roomHandler(Protocol p)
{
    QString type = p["type"].toString();
    int port = p["port"].toInt();
    if(type == "create"){ //创建房间
        //创建房间
        WidgetManager::getInstance()->getRoomWidget()->setWindowTitle(
                    p["username"].toString());
        WidgetManager::getInstance()->getRoomWidget()->setUsername(
                    p["username"].toString());
        WidgetManager::getInstance()->getRoomWidget()->setRoomname(
                    p["roomname"].toString());
        WidgetManager::getInstance()->getRoomWidget()->setPort(port);
        WidgetManager::getInstance()->getRoomWidget()->myInit();

        WidgetManager::getInstance()->getHallWidget()->hide();
        WidgetManager::getInstance()->getRoomWidget()->show();
    }else if(type == "join"){ //加入房间
        WidgetManager::getInstance()->getRoomWidget()->setWindowTitle(
                    p["username"].toString());
        WidgetManager::getInstance()->getRoomWidget()->setUsername(
                    p["username"].toString());
        WidgetManager::getInstance()->getRoomWidget()->setRoomname(
                    p["roomname"].toString());
        WidgetManager::getInstance()->getRoomWidget()->setPort(port);
        WidgetManager::getInstance()->getRoomWidget()->myInit();

        WidgetManager::getInstance()->getHallWidget()->hide();
        WidgetManager::getInstance()->getRoomWidget()->show();
    }else if(type == "quit"){ //退出房间
        if(!p["message"].toString().isEmpty()){
            QMessageBox::information(WidgetManager::getInstance()->getRoomWidget(),
                                     "退出信息",p["message"].toString());
        }
        WidgetManager::getInstance()->getRoomWidget()->myInit();
        WidgetManager::getInstance()->getRoomWidget()->hide();
        WidgetManager::getInstance()->getHallWidget()->show();
    }else if(type == "refresh"){ //刷新房间列表
        QJsonArray array = p["roomname"].toArray();
        QStringList roomList;
        int i=0;
        for(i=0;i<array.size();i++){
            roomList.append(array[i].toString());
        }

        WidgetManager::getInstance()->getHallWidget()->refleshRoomname(roomList);
    }else if(type == "refreshUser"){  //刷新用户列表
        QJsonArray array = p["username"].toArray();
        QStringList userList;
        int i=0;
        for(i=0;i<array.size();i++){
           userList.append(array[i].toString());
        }
        WidgetManager::getInstance()->getRoomWidget()->refleshUsername(userList);
    }
}

void ClientSocket::chatHandler(Protocol p)  //聊天和弹幕
{
    QString type = p["type"].toString();
    if(type == "chat"){
        QString text = p["text"].toString();
        WidgetManager::getInstance()->getRoomWidget()->appendText(text);

        QStringList ls=text.split(':');
        int i=ls.size()-1;
        text=ls[i];
        WidgetManager::getInstance()->getRoomWidget()->sendScrollText(text);
    }
}


void ClientSocket::chargeHandler(Protocol p) //充值
{
    QString type = p["type"].toString();

    if(type == "success"){
        //充值成功
        QMessageBox::information(WidgetManager::getInstance()->getChargeWidget(), "充值信息", p["message"].toString());
    }else if(type == "failed"){
        //充值失败
        QMessageBox::warning(WidgetManager::getInstance()->getChargeWidget(), "充值信息", p["message"].toString());
    }
}

void ClientSocket::giftHandler(Protocol p) //送礼
{
    QString type = p["type"].toString();

    if(type == "success"){
        //送礼成功
        WidgetManager::getInstance()->getGiftWidget()->hide();
        QMessageBox::information(WidgetManager::getInstance()->getRoomWidget(), "送礼信息", p["message"].toString());

    }else if(type == "failed"){
        //送礼失败
        WidgetManager::getInstance()->getGiftWidget()->hide();
        QMessageBox::warning(WidgetManager::getInstance()->getRoomWidget(), "送礼信息", p["message"].toString());

    }else if(type == "gift"){
        //提示信息
        QString text = p["text"].toString();

        WidgetManager::getInstance()->getGiftWidget()->hide();
        WidgetManager::getInstance()->getRoomWidget()->sendScrollGift(text);
    }
}

#include "clientsocket.h"
#include <QDebug>
#include <QJsonArray>

#include "sql/sqldao.h"
#include "room/roommanager.h"
#include <QDateTime>

ClientSocket::ClientSocket(QTcpSocket *socket,QObject *parent)
    : QObject(parent),socket(socket)
{
    QObject::connect(this->socket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
    QObject::connect(this->socket, SIGNAL(disconnected()), this, SLOT(onDisConnected()));
}
void ClientSocket::onReadyRead()
{
    //读取数据
    buffer += this->socket->readAll();
    Protocol p;

    while(p.unpack(buffer)){
        //拆解成功
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
        }
    }
}
void ClientSocket::onDisConnected()
{
    this->socket->deleteLater();
    this->deleteLater();
}
void ClientSocket::registHandler(Protocol p)
{
    QString type = p["type"].toString();
    QString username = p["username"].toString();
    QString userpwd = p["userpwd"].toString();

    Protocol pro;
    if(type == "register"){

        pro.setType(Protocol::regist);
        pro["username"] = username;
        //1. 插入用户
        SqlDao sd;
        if(sd.insertUser(User(username, userpwd, 0))){
            //成功
            pro["type"] = "success";
            pro["message"] = "注册成功";
        }else{
            //失败
            pro["type"] = "failed";
            pro["message"] = "注册失败";
        }
    }

    this->socket->write(pro.pack());
}

void ClientSocket::loginHandler(Protocol p)
{
    SqlDao sd;

    QString username = p["username"].toString();
    QString userpwd = p["userpwd"].toString();
    User user;

    QString type = p["type"].toString();
    Protocol pro;
    pro.setType(Protocol::login);
    do{
        if(type == "login"){
            //登录
            if(!sd.selectUserByUsername(username,user)){
                //没找到
                pro["type"] = "failed";
                pro["message"] = "无此用户";
                break;
            }
            if(user.getOnline()!=0){
                //在线
                pro["type"] = "failed";
                pro["message"] = "重复登录";
                break;
            }
            if(user.getUserpwd() != userpwd){
                //密码错误
                pro["type"] = "failed";
                pro["message"] = "密码错误";
                break;
            }

            //登录成功
            pro["type"] = "success";
            pro["message"] = "登录成功";
            pro["username"] = username;

            sd.updateUserOnline(username,1);

        }else if(type == "quit"){
            //退出登录
            sd.updateUserOnline(username,0);
            pro["type"] = "quit";
        }
    }while(0);

    this->socket->write(pro.pack());

}

void ClientSocket:: roomHandler(Protocol p)
{
    QString type = p["type"].toString();
    QString roomname = p["roomname"].toString();
    QString username = p["username"].toString();

    Protocol pro;
    pro.setType(Protocol::room);
    pro["roomname"] = roomname;
    pro["username"] = username;

    if(type == "create"){
        //创建房间
        Room room;
        room.setRoomname(roomname);
        int port = RoomManager::getInstance()->applyPort();
        room.setPort(port);

        Guest guest;
        guest.setUsername(username);
        guest.setClientSocket(this);
        room.getGuests().append(guest);

        RoomManager::getInstance()->getRooms().append(room);
        pro["type"] = "create";
        pro["port"] = port;

        refreshRoom();
        refreshUser(roomname);
    }else if(type == "join"){
        //加入房间
        Room* room = RoomManager::getInstance()->getRoomByRoomname(roomname);
        if(room == nullptr) return;
        int port = room->getPort();

        Guest guest;
        guest.setUsername(username);
        guest.setClientSocket(this);

        room->getGuests().append(guest);
        if(roomname == "") return;
        pro["type"] = "join";
        pro["port"] = port;

        //刷新用户列表
        refreshUser(roomname);
    }else if(type == "quit"){
        //退出房间

        Room* room = RoomManager::getInstance()->getRoomByRoomname(roomname);
        if(room == nullptr) return;
        if(roomname == username){
            //房主退房
            {
                Protocol pro;
                pro.setType(Protocol::room);
                pro["type"] = "quit";
                pro["message"] = "因房主退出，强制退出";

                Room* room = RoomManager::getInstance()->getRoomByRoomname(roomname);
                if(room){
                    QVector<Guest>::iterator it;
                    for(it = room->getGuests().begin(); it != room->getGuests().end(); ++it){
                        if(it->getUsername() == username)   continue;
                        it->getClientSocket()->socket->write(pro.pack());
                    }
                }
            }
            RoomManager::getInstance()->eraseRoomByRoomname(roomname);
            refreshRoom();
        }else{
            bool flag = false;
            QVector<Guest>::iterator it;
            for(it = room->getGuests().begin();it != room->getGuests().end();it++){
                if(it->getUsername() == username){
                    //找到该用户
                    room->getGuests().erase(it);
                    flag = true;
                    break;
                }
            }
            refreshUser(roomname);
            if(!flag) return ;
        }

        pro["type"] = "quit";
        if(roomname == "") return;
    }else if(type == "refresh"){
        pro["type"] = "refresh";
        QJsonArray roomList;
        QVector<Room>::iterator it;
        for(it = RoomManager::getInstance()->getRooms().begin();
            it != RoomManager::getInstance()->getRooms().end(); ++it){
                if(it->getRoomname() == "") continue;
                roomList.append(it->getRoomname());
            }

        pro["roomname"] = roomList;//数组
    }
    this->socket->write(pro.pack());

}

void ClientSocket::chatHandler(Protocol p)
{
    QString type = p["type"].toString();
    if(type == "chat"){
        QString username = p["username"].toString();
        QString roomname = p["roomname"].toString();
        QString text = p["text"].toString();

            //谁 几点 ： 内容
        text = username + " " + QDateTime::currentDateTime().toString()
                    + " :\n" + text;

        Protocol pro;
        pro.setType(Protocol::chat);
        pro["type"] = "chat";
        pro["roomname"] = roomname;
        pro["username"] = username;
        pro["text"] = text;

        Room* room = RoomManager::getInstance()->getRoomByRoomname(roomname);
        QVector<Guest>::iterator it;
        for(it = room->getGuests().begin(); it != room->getGuests().end(); ++it){
            it->getClientSocket()->socket->write(pro.pack());
        }
    }
}

void ClientSocket::chargeHandler(Protocol p)
{
    SqlDao sd;

    QString type = p["type"].toString();
    QString username = p["username"].toString();
    int chargenum = p["chargenum"].toInt();

    User user;

    Protocol pro;
    pro.setType(Protocol::charge);

    if(type == "charge"){
        if(sd.selectUserByUsername(username,user)){
            int balance = user.getBalance();
            balance += chargenum;
            sd.updateUserBalance(username,balance);

            pro["type"] = "success";
            pro["message"] = "充值成功";
        }else{
            pro["type"] = "failed";
            pro["message"] = "充值失败";
        }
    }

    this->socket->write(pro.pack());
}

void ClientSocket::giftHandler(Protocol p)
{
    SqlDao sd;
    User user;
    QString type = p["type"].toString();
    QString roomname = p["roomname"].toString();
    QString username = p["username"].toString();
    int money = p["money"].toInt();

    Protocol pro;
    pro.setType(Protocol::gift);
    pro["roomname"] = roomname;
    pro["username"] = username;

    Room* room = RoomManager::getInstance()->getRoomByRoomname(roomname);
    if(room == nullptr) return;

    if(roomname == username){
        //房主不能给自己送礼
        pro["message"] = "房主不能送礼";
        pro["type"] = "failed";
    }else{
        QVector<Guest>::iterator it;
        for(it = room->getGuests().begin();it != room->getGuests().end();it++){
            if(it->getUsername() == username){
                //找到送礼用户
                if(sd.selectUserByUsername(username,user)){
                    int balance = user.getBalance();
                    int temp = balance - money;
                    if(temp > 0 || temp==0){
                        sd.updateUserBalance(username,temp);
                        pro["type"] = "success";
                        pro["message"] = "送礼成功";

                        QVector<Guest>::iterator its;
                        for(its = room->getGuests().begin();its != room->getGuests().end();its++){
                            if(its->getUsername() == roomname){
                                //找到房主
                                User users;
                                if(sd.selectUserByUsername(roomname,users)){
                                    int balance = users.getBalance();
                                    balance +=money;
                                    sd.updateUserBalance(roomname,balance);
                                }
                                break;
                            }
                        }
                        giftScroll(username,roomname,money);

                    }else if(temp < 0){
                        pro["type"] = "failed";
                        pro["message"] = "余额不足";
                    }

                }
                    break;
            }
        }

    }
    this->socket->write(pro.pack());
}

void ClientSocket::giftScroll(QString username, QString roomname, int money)
{
    QString text;
    Protocol pro;
    pro.setType(Protocol::gift);
    pro["type"] = "gift";
    switch(money){
    case 10:
        text = "用户："+ username + " " + "送出了一颗红心";
        pro["text"] = text;
        break;
    case 50:
        text = "用户："+ username + " " + "送出了一辆跑车";
        pro["text"] = text;
        break;
    case 100:
        text = "用户："+ username + " " + "送出了一艘火箭";
        pro["text"] = text;
        break;
    case 200:
        text = "用户："+ username + " " + "送出了一艘潜艇";
        pro["text"] = text;
        break;
    }

    Room* room = RoomManager::getInstance()->getRoomByRoomname(roomname);
    QVector<Guest>::iterator it;
    for(it = room->getGuests().begin(); it != room->getGuests().end(); ++it){
        it->getClientSocket()->socket->write(pro.pack());
    }

}

void ClientSocket::refreshRoom()
{
    Protocol pro;
    pro.setType(Protocol::room);
    pro["type"] = "refresh";
    QJsonArray roomList;
    QVector<Room>::iterator it;
    for(it = RoomManager::getInstance()->getRooms().begin();
        it != RoomManager::getInstance()->getRooms().end();it++){
        if(it->getRoomname() == "") continue;
        roomList.append(it->getRoomname());
    }

    pro["roomname"] = roomList;//所有的房间名

    Room* room = RoomManager::getInstance()->getRoomByRoomname("");
    if(room){
        QVector<Guest>::iterator it;
        for(it = room->getGuests().begin();it != room->getGuests().end();it++){
            it->getClientSocket()->socket->write(pro.pack());
        }
    }
}

void ClientSocket::refreshUser(QString roomname)
{
    Protocol pro;
    pro.setType(Protocol::room);
    pro["type"] = "refreshUser";
    QJsonArray userList;

    Room* room = RoomManager::getInstance()->getRoomByRoomname(roomname);
    if(room){
        QVector<Guest>::iterator it;
        for(it = room->getGuests().begin();it != room->getGuests().end();it++){
            userList.append(it->getUsername());
        }
        pro["username"] = userList;
        for(it = room->getGuests().begin();it != room->getGuests().end();it++){
            it->getClientSocket()->socket->write(pro.pack());
        }
    }
}


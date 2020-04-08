#include "roommanager.h"

RoomManager::RoomManager()
{
    Room room;
    room.setRoomname("");//没有名字，表示大厅=下表为0的，就是大厅
    rooms.append(room);
}

RoomManager* RoomManager::instance = new RoomManager;

RoomManager* RoomManager::getInstance()
{
    return instance;
}

Room* RoomManager::getRoomByRoomname(const QString &roomname)
{
    int i=0;
    for(i = 0;i<rooms.size();i++){
        if(rooms[i].getRoomname() == roomname) return &rooms[i];

    }
    return nullptr;
}

bool RoomManager::eraseRoomByRoomname(const QString &roomname)
{
    QVector<Room>::iterator it;
    for(it = rooms.begin();it != rooms.end();it++){
        if(it->getRoomname() == roomname){
            rooms.erase(it);
            return true;
        }
    }

    return false;
}

int RoomManager::applyPort()
{
    int port = 6666;

    QVector<Room>::iterator it;
    do{
        for(it = this->getInstance()->getRooms().begin();
            it != this->getInstance()->getRooms().end();it++){
            if(it->getPort()== port){
                port++;//找一个没用过的端口号
                break;//提前退出
            }
        }
    }while(it !=this->getInstance()->getRooms().end());

    return port;
}

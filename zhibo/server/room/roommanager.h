#ifndef ROOMMANAGER_H
#define ROOMMANAGER_H

#include "room.h"
#include <QVector>

class RoomManager
{
private:
    RoomManager();
    static RoomManager* instance;

    QVector<Room> rooms;


public:
    static RoomManager* getInstance();
    inline QVector<Room>& getRooms(){
        return rooms;
    }
    Room* getRoomByRoomname(const QString& roomname);
    bool eraseRoomByRoomname(const QString& roomname);

    int applyPort();
};

#endif // ROOMMANAGER_H

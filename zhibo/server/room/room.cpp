#include "room.h"

int Room::getPort() const
{
    return port;
}

void Room::setPort(int value)
{
    port = value;
}

Room::Room()
{
    
}

QString Room::getRoomname() const
{
    return roomname;
}

void Room::setRoomname(const QString &value)
{
    roomname = value;
}

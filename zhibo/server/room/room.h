#ifndef ROOM_H
#define ROOM_H

#include <QString>
#include <QVector>
#include "guest.h"

class Room
{
private:
    QString roomname;
    QVector<Guest> guests;

    int port;
public:
    Room();

    QString getRoomname() const;
    void setRoomname(const QString &value);

    inline QVector<Guest>& getGuests(){
        return guests;
    }
    int getPort() const;
    void setPort(int value);
};

#endif // ROOM_H

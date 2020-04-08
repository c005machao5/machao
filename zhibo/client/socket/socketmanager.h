#ifndef SOCKETMANAGER_H
#define SOCKETMANAGER_H

#include "clientsocket.h"
class SocketManager
{
private:
    SocketManager();
    static SocketManager* instance;

    ClientSocket* cs;
public:
    static SocketManager* getInstance();

    inline qint64 write(const QByteArray& array){
        return cs->write(array);
    }
};

#endif // SOCKETMANAGER_H

#ifndef GUEST_H
#define GUEST_H

#include <QString>
#include "socket/clientsocket.h"

class Guest
{
private:
    QString username;
    ClientSocket* clientSocket;

public:
    Guest();

    QString getUsername() const;
    void setUsername(const QString &value);
    ClientSocket *getClientSocket() const;
    void setClientSocket(ClientSocket *value);
};

#endif // GUEST_H

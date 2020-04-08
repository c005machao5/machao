#include "guest.h"

Guest::Guest()
{

}
QString Guest::getUsername() const
{
    return username;
}

void Guest::setUsername(const QString &value)
{
    username = value;
}

ClientSocket *Guest::getClientSocket() const
{
    return clientSocket;
}

void Guest::setClientSocket(ClientSocket *value)
{
    clientSocket = value;
}

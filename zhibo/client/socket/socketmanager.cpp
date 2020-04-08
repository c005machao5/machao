#include "socketmanager.h"

#define ADDR "192.168.1.101"
#define PORT (11111)
SocketManager::SocketManager()
    :cs(new ClientSocket)
{
    cs->initSocket(ADDR,PORT);
}
SocketManager* SocketManager::instance = nullptr;

SocketManager* SocketManager::getInstance()
{
    if(instance == nullptr) instance = new SocketManager;
    return instance;
}
